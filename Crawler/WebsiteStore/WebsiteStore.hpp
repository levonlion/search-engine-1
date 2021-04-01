#ifndef WebsiteStore_hpp
#define WebsiteStore_hpp

#include <unordered_map>
#include <vector>
#include "Website.hpp"

class WebsiteStore {
    
private:

    /**
     * All websites.
     */
    std::unordered_map<std::string, Website> all;

public:
    
    WebsiteStore() = default;
    
    WebsiteStore(const std::vector<Website>& websites);
    
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
