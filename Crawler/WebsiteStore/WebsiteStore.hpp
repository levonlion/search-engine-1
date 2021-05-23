#ifndef WebsiteStore_hpp
#define WebsiteStore_hpp

#include <unordered_map>
#include <vector>
#include <mysqlx/xdevapi.h>
#include <memory>

#include "Website.hpp"

class WebsiteStore {
    
private:
    
    std::shared_ptr<mysqlx::Client> client;

public:
    
    WebsiteStore(std::shared_ptr<mysqlx::Client> client);
    
    /**
     * @return All websites.
     */
    std::vector<Website> getAll() const;
    
    /**
     * Add website to store.
     */
    void add(const Website& website);
    
    /**
     * Updates information for the website.
     */
    void update(const Website& website);
    
};


#endif /* WebsiteStore_hpp */
