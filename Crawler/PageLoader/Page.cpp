#include "Page.hpp"

Page::Page(const std::string& s) {
    body = s;
}

int Page::isError() const {
    return false;
}

const std::string& Page::getBody() const {
    return body;
}

int Page::getStatus() const {
    return -1;
}
