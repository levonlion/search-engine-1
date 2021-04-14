#include "Parser.hpp"

#include <gumbo.h>

#include <optional>
#include <algorithm>

Parser::Parser(const std::string& url, const std::string& html) {
    this->url   = url;
    this->html  = html;
    
    this->urlHost   = this->host(url).value();
    this->urlPath   = this->path(url).value();
    this->urlScheme = this->scheme(url).value();
}

void Parser::extractUrls(GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    
    if (node->v.element.tag == GUMBO_TAG_A) {
        GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
        if (href == nullptr || href->value == nullptr) {
            return;
        }
        
        std::string parsedUrl(href->value);
        
        if (scheme(parsedUrl).has_value()) {
            if (host(parsedUrl).value() == this->urlHost) {
                this->urls.push_back(parsedUrl);
            }
        } else if (parsedUrl.size() > 1 && parsedUrl.front() == '/') {
            if (parsedUrl[1] != '/') {
                parsedUrl = this->urlScheme + "://" + this->urlHost + parsedUrl;
                this->urls.push_back(parsedUrl);
            }
        } else if (!parsedUrl.empty() && parsedUrl.front() != '#') {
            std::string::iterator backslashPosition = std::find(this->urlPath.rbegin(), this->urlPath.rend(), '/').base();
            std::string urlPath(this->urlPath.begin(), ++backslashPosition);
            parsedUrl = this->urlScheme + "://" + this->urlHost + urlPath + parsedUrl;
            this->urls.push_back(parsedUrl);
        }
    }
    
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        this->extractUrls(static_cast<GumboNode*>(children->data[i]));
    }
    
}

void Parser::parse() {
    GumboOutput* output = gumbo_parse(this->html.c_str());
    this->extractUrls(output->root);
    this->allText = this->extractCleanText(output->root);
    this->title = this->extractTitle(output->root);
    this->extractDescription(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

const std::vector<std::string>& Parser::getUrls() const {
    return this->urls;
}

std::optional<std::string> Parser::scheme(const std::string& url) {
    
    auto found = url.find("://");
    if (found != std::string::npos) {
        return std::string(url, 0, found);
    }
    
    return {};
}

std::optional<std::string> Parser::host(const std::string& url) {
    
    auto beginIndex = url.find("://");
    if (beginIndex == std::string::npos) {
        return {};
    }
    
    beginIndex += 3;
    
    auto userInfoEnd = url.find('@', beginIndex);
    if (userInfoEnd != std::string::npos) {
        beginIndex = userInfoEnd + 1;
    }
    
    auto endIndex = url.find(':', beginIndex);
    if (endIndex != std::string::npos) {
        return std::string(url, beginIndex, endIndex - beginIndex);
    }
    
    endIndex = url.find('/', beginIndex);
    if (endIndex != std::string::npos) {
        return std::string(url, beginIndex, endIndex - beginIndex);
    }
    
    return std::string(url, beginIndex, url.size() - beginIndex);;
}

std::optional<std::string> Parser::path(const std::string& url) {
    auto beginIndex = url.find(":");
    if (beginIndex == std::string::npos) {
        return {};
    }
    
    // For ignoring ://
    beginIndex += 3;
    
    beginIndex = url.find('/', beginIndex);
    if (beginIndex == std::string::npos) {
        return "/";
    }
    
    auto endIndex = url.rfind('/');
    if (endIndex != std::string::npos) {
        return std::string(url, beginIndex, endIndex - beginIndex);
    }
    
    return "/";
}

const std::string& Parser::getTitle() const {
    return this->title;
}

const std::string& Parser::getDescription() const {
    return this->description;
}

const std::string& Parser::getAllText() const {
    return this->allText;
}

std::string Parser::extractCleanText(GumboNode* node) const {
    if (node->type == GUMBO_NODE_TEXT) {
        return std::string(node->v.text.text);
    } else if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag != GUMBO_TAG_SCRIPT && node->v.element.tag != GUMBO_TAG_STYLE) {
        std::string contents;
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            const std::string text = this->extractCleanText((GumboNode*) children->data[i]);
            if (i != 0 && !text.empty()) {
                contents.append(" ");
            }
            contents.append(text);
        }
        return contents;
    } else {
        return "";
    }
}

std::string Parser::extractTitle(const GumboNode* root) const {
    if (root->type != GUMBO_NODE_ELEMENT || root->v.element.children.length < 2) {
        return "";
    }
    
    const GumboVector* rootChildren = &root->v.element.children;
    GumboNode* head = NULL;
    for (int i = 0; i < rootChildren->length; ++i) {
        GumboNode* child = (GumboNode*) rootChildren->data[i];
        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD) {
            head = child;
            break;
        }
    }
    
    if (head == NULL) {
        return "";
    }
    
    GumboVector* head_children = &head->v.element.children;
    for (int i = 0; i < head_children->length; ++i) {
        GumboNode* child = (GumboNode*) head_children->data[i];
        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE) {
            if (child->v.element.children.length != 1) {
                // empty title
                return "";
            }
            GumboNode* title_text = (GumboNode*) child->v.element.children.data[0];
            assert(title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE);
            return title_text->v.text.text;
        }
    }
    // no title found
    return "";
}

void Parser::extractDescription(GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    
    if (node->v.element.tag == GUMBO_TAG_META) {
        GumboAttribute* name = gumbo_get_attribute(&node->v.element.attributes, "name");
        if (name == nullptr || name->value == nullptr || name->value != std::string("description")) {
            return;
        }
        
        GumboAttribute* content = gumbo_get_attribute(&node->v.element.attributes, "content");
        if (content == nullptr || content->value == nullptr) {
            return;
        }

        this->description = content->value;
        return;
    }
    
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        this->extractDescription(static_cast<GumboNode*>(children->data[i]));
    }
    
    return;
}
