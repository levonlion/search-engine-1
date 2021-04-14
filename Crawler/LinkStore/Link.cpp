#include "Link.hpp"
#include "LinkStatus.hpp"

Link::Link(const std::string& url, const std::string& domain, const LinkStatus status, time_t time) {
    this->url = url;
    this->domain = domain;
    this->status = status;
    this->lastLoadTime = time;
}

time_t Link::getLastLoadTime() const {
    return lastLoadTime;
}

std::string Link::getUrl() const {
    return url;
}

std::string Link::getDomain() const {
    return domain;
}

LinkStatus Link::getStatus() const {
    return status;
}

bool Link::operator==(const Link& other) {
    return this->url == other.url;
}
