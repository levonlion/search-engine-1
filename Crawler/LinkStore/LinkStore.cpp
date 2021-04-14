#include "LinkStore.hpp"
#include <algorithm>

const std::vector<Link>& LinkStore::getAll() const {
    return all;
}

std::optional<Link> LinkStore::getBy(const std::string& url) const {
    for (const auto& link : all) {
        if (link.getUrl() == url) {
            return link;
        }
    }
    return {};
}

std::vector<Link> LinkStore::getBy(const std::string& domain, const LinkStatus status, std::size_t count) const {
    std::vector<Link> res;
    
    for (const auto& link : all) {
        if (count == 0) {
            break;
        }
        if (link.getStatus() == status) {
            res.push_back(link);
            --count;
        }
    }
    
    return res;
}

void LinkStore::add(const Link& link) {
    all.push_back(link);
}

void LinkStore::update(const Link& link) {
    const auto& linkIter = std::find(all.begin(), all.end(), link);
    if (linkIter != all.end()) {
        *linkIter = link;
    } else {
        all.push_back(link);
    }
    
}

std::size_t LinkStore::count() const {
    return this->all.size();
}
