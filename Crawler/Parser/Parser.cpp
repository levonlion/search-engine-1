#include "Parser.hpp"

#include <gumbo.h>

Parser::Parser(const std::string& url, const std::string& html) {
    this->url = url;
    this->html = html;
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

        //TODO: make relative to absolute (\ is means that we need to concatenate it home url and no \ means that we need concatenate it with current url, we can get it from libcurl), skip out of rau links, skip # and skip empties
        this->urls.push_back(std::string(href->value));
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

