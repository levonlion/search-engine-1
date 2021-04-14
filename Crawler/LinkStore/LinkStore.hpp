#ifndef LinkStore_hpp
#define LinkStore_hpp

#include <vector>
#include <string>
#include <optional>
#include "Link.hpp"

class LinkStore {

private:
    
    std::vector<Link> all;
    
public:
    
    const std::vector<Link>& getAll() const;
    
    std::optional<Link> getBy(const std::string& url) const;
    
    std::vector<Link> getBy(const std::string& domain, const LinkStatus status, std::size_t count) const;
    
    void add(const Link& link);
    
    void update(const Link& link);
    
    std::size_t count() const;
};


#endif /* LinkStore_hpp */
