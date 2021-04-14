#include "Document.hpp"

Document::Document(const std::string& url, const std::string& title, const std::string& description, const std::string& allText) {
    this->url = url;
    this->title = title;
    this->description = description;
    this->allText = allText;
}


const std::string& Document::getUrl() const {
    return this->url;
}

const std::string& Document::getDescription() const {
    return this->description;
}

const std::string& Document::getTitle() const {
    return this->title;
}

const std::string& Document::getAllText() const {
    return this->allText;
}
