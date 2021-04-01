#include "WebsiteStore.hpp"

#include <algorithm>
#include "Website.hpp"

WebsiteStore::WebsiteStore(const std::vector<Website>& websites) {
    for (const auto& website : websites) {
        this->add(website);
    }
}

std::vector<Website> WebsiteStore::getAll() const {
    std::vector<Website> v;
    
    for (const auto& elem : all) {
        v.push_back(elem.second);
    }
    
    return v;
}

void WebsiteStore::add(const Website& website) {
    all.insert({ website.getDomain(), website });
}

void WebsiteStore::update(const Website& website) {
    all[website.getDomain()] = website;
}
