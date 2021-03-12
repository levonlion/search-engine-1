#include "Page.hpp"

Page::Page(const std::string& url, const std::string& body, statusType status, errorType error) {
    this->url = url;
    this->body = body;
    this->status = status;
    this->error = error;
}

Page::errorType Page::isError() const {
    return error;
}

const std::string& Page::getBody() const {
    return body;
}

Page::statusType Page::getStatus() const {
    return status;
}

const std::string& Page::getUrl() const {
    return url;
}
