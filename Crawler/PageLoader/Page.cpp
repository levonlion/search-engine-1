#include "Page.hpp"

Page::Page(const std::string& body, statusType status, errorType error) {
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
