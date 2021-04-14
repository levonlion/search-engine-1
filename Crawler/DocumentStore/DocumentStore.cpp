#include "DocumentStore.hpp"

std::vector<Document> DocumentStore::getAll() const {
    
    std::vector<Document> res;
    
    for (const auto& elem : this->all) {
        res.push_back(elem.second);
    }
    
    return res;
}

void DocumentStore::save(const Document& document) {
    this->all[document.getUrl()] = document;
}

std::size_t DocumentStore::count() const {
    return this->all.size();
}
