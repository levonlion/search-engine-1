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

    GumboVector *children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        this->extractUrls(static_cast<GumboNode*>(children->data[i]));
    }

}

void Parser::parse() {
    GumboOutput* output = gumbo_parse(this->html.c_str());
    this->extractUrls(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

const std::vector<std::string>& Parser::getUrls() const {
    return this->urls;
}

std::optional<std::string> Parser::scheme(const std::string& url) {
    
    auto found = url.find(":");
    if (found != std::string::npos) {
        return std::string(url, 0, found);
    }
    
    return {};
}

std::optional<std::string> Parser::host(const std::string& url) {
    
    auto beginIndex = url.find(":");
    if (beginIndex == std::string::npos) {
        return {};
    }
    
    // For ignoring ://
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
        return std::string(url, beginIndex, endIndex - beginIndex - 1);
    }
    
    return "/";
}
