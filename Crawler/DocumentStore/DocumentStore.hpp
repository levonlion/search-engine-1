#ifndef DocumentStore_hpp
#define DocumentStore_hpp

#include <unordered_map>
#include <string>
#include <vector>
#include "Document.hpp"

class DocumentStore {
    
private:
    
    std::unordered_map<std::string, Document> all;
    
public:
    
    std::vector<Document> getAll() const;
    
    void save(const Document& document);
};


#endif /* DocumentStore_hpp */
