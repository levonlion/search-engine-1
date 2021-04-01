#include "Website.hpp"

Website::Website(const std::string& domain, const std::string& homepage, time_t time) {
    this->domain = domain;
    this->homepage = homepage;
    this->lastCrawlingTime = time;
}

std::string Website::getDomain() const {
    return domain;
}

std::string Website::getHomepage() const {
    return homepage;
}

time_t Website::getLastCrawlingTime() const {
    return lastCrawlingTime;
}
