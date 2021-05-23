#include "Link.hpp"
#include "LinkStatus.hpp"

Link::Link(int id, const std::string& url, const std::string& domain, const LinkStatus status, time_t time) {
    this->id = id;
    this->url = url;
    this->domain = domain;
    this->status = status;
    this->lastLoadTime = time;
}

time_t Link::getLastLoadTime() const {
    return this->lastLoadTime;
}

std::string Link::getUrl() const {
    return this->url;
}

std::string Link::getDomain() const {
    return this->domain;
}

LinkStatus Link::getStatus() const {
    return this->status;
}

int Link::getId() const {
    return this->id;
}

bool Link::operator==(const Link& other) {
    return this->url == other.url;
}
