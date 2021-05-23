#ifndef Link_hpp
#define Link_hpp

#include <string>
#include <ctime>
#include "LinkStatus.hpp"

class Link {
    
private:
    
    /**
     * The ID (identity document number) of the link.
     */
    int id;
    
    /**
     * The effective url.
     */
    std::string url;

    
    std::string domain;
    
    
    LinkStatus status;
    
    time_t lastLoadTime;

public:
    
    Link(int id, const std::string& url, const std::string& domain, const LinkStatus status, time_t time);
    
    time_t getLastLoadTime() const;
    
    std::string getUrl() const;

    std::string getDomain() const;
    
    LinkStatus getStatus() const;
    
    int getId() const;
    
    bool operator==(const Link& other);
};


#endif /* Link_hpp */
