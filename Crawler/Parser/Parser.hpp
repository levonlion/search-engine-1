#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include <vector>

#include <gumbo.h>

class Parser {
    
private:
    
    /**
     * The effective url.
     */
    std::string url;
    
    /**
     * The entire HTML document.
     */
    std::string html;
    
    /**
     * All urls.
     */
    std::vector<std::string> urls;
    
    /**
     * Title inside <head>.
     */
    std::string title;
    std::string description;
    std::string allText;
    
private:

    /**
     * Extract all urls.
     */
    void extractUrls(GumboNode* node);
    
public:
    
    /**
     * Parse the HTML document.
     * @param url The effective url.
     * @param html The entire HTML document.
     */
    Parser(const std::string& url, const std::string& html);
    
    /**
     * Parse the HTML document.
     */
    void parse();
    
    /**
     * @return All urls.
     */
    const std::vector<std::string>& getUrls() const;
    

};


#endif /* Parser_hpp */
