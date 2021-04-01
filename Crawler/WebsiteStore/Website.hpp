#ifndef Website_hpp
#define Website_hpp

#include <string>

class Website {

private:
    
    /**
     * The domain of the site. For example:
     *    The domain of https://example.com/ is example.com
     */
    std::string domain;
    
    /**
     * The homepage url.
     */
    std::string homepage;
    
    time_t lastCrawlingTime;
    //...
    
public:
    
    Website() = default;
    
    /**
     * @param domain The domain of the site. For example: the domain of https://example.com/ is example.com
     * @param homepage The homepage url.
     * @param time The last crawling time.
     */
    Website(const std::string& domain, const std::string& homepage, time_t time);
    
    Website(const Website&) = default;
    
    Website(Website&&) = default;
    
    Website& operator=(const Website&) = default;
    
    std::string getDomain() const;
    
    std::string getHomepage() const;
    
    time_t getLastCrawlingTime() const;
};


#endif /* Website_hpp */
