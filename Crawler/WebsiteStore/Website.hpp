#ifndef Website_hpp
#define Website_hpp

#include <string>

class Website {

private:
    
    /**
     * The ID (identity document number) of the link.
     */
    int id;
    
    /**
     * The domain of the site.
     */
    std::string domain;
    
    /**
     * The homepage url.
     */
    std::string homepage;
    
    /**
     * The last crawling time.
     */
    time_t lastCrawlingTime;
    
public:
        
    /**
     * @param id The ID (identity document) of website.
     * @param domain The domain of the site.
     * @param homepage The homepage url.
     * @param time The last crawling time.
     */
    Website(int id, const std::string& domain, const std::string& homepage, time_t time);
    
    const std::string& getDomain() const;
    
    const std::string& getHomepage() const;
    
    time_t getLastCrawlingTime() const;
    
    int getId() const;
};


#endif /* Website_hpp */
