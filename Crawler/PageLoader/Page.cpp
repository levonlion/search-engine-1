#include "Page.hpp"

Page::Page(const std::string& url, const std::string& body, statusType status, errorType error) {
    this->url = url;
    this->body = body;
    this->status = status;
    this->error = error;
}

Page::errorType Page::isError() const {
    return this->error;
}

const std::string& Page::getBody() const {
    return this->body;
}

Page::statusType Page::getStatus() const {
    return this->status;
}

const std::string& Page::getUrl() const {
    return this->url;
}
