#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include <vector>

#include <gumbo.h>

class Parser {
    
private:
    
    std::string url;
    std::string html;
    std::vector<std::string> urls;
    std::string title;
    std::string description;
    std::string allText;
    
private:

    void extractUrls(GumboNode* node);
    
public:
    
    /**
     * Parse the HTML document.
     * @param html The entire HTML document
     */
    Parser(const std::string& url, const std::string& html);
    
    void parse();
    
    const std::vector<std::string>& getUrls() const;
    

};


#endif /* Parser_hpp */
