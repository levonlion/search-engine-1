#ifndef LinkStore_hpp
#define LinkStore_hpp

#include <vector>
#include <string>
#include <optional>
#include <mysqlx/xdevapi.h>
#include <memory>

#include "Link.hpp"

class LinkStore {

private:
    
    std::shared_ptr<mysqlx::Client> client;
    
public:
    
    LinkStore(std::shared_ptr<mysqlx::Client> client);
    
    std::vector<Link> getAll() const;
    
    std::optional<Link> getBy(const std::string& url) const;
    
    /**
     * @param count The max size is the size of the unsigned int.
     */
    std::vector<Link> getBy(const std::string& domain, const LinkStatus status, std::size_t count) const;
    
    void add(const Link& link);
    
    void update(const Link& link);
    
    std::size_t count() const;
};


#endif /* LinkStore_hpp */
