#include "Website.hpp"

Website::Website(int id, const std::string& domain, const std::string& homepage, time_t time) {
    this->id = id;
    this->domain = domain;
    this->homepage = homepage;
    this->lastCrawlingTime = time;
}

const std::string& Website::getDomain() const {
    return this->domain;
}

const std::string& Website::getHomepage() const {
    return this->homepage;
}

time_t Website::getLastCrawlingTime() const {
    return this->lastCrawlingTime;
}

int Website::getId() const {
    return this->id;
}
