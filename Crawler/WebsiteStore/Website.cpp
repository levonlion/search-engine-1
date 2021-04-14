#include "Website.hpp"

Website::Website(const std::string& domain, const std::string& homepage, time_t time) {
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
