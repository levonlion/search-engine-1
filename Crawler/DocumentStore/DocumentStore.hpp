#ifndef DocumentStore_hpp
#define DocumentStore_hpp

#include <unordered_map>
#include <string>
#include <vector>
#include "Document.hpp"
#include <mysqlx/xdevapi.h>

class DocumentStore {
    
private:
    
    std::shared_ptr<mysqlx::Client> client;
    
public:
    
    DocumentStore(std::shared_ptr<mysqlx::Client> client);
    
    std::vector<Document> getAll() const;
    
    void save(const Document& document);
    
    std::size_t count() const;
};


#endif /* DocumentStore_hpp */
