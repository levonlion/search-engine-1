#ifndef PageLoader_hpp
#define PageLoader_hpp

#include <string>
#include "Page.hpp"

class PageLoader {
    
public:
    
    PageLoader();

    /**
     * @return The content of HTML document.
     */
    Page load(const std::string& url);
    
private:
    
    /**
     * Callback function for writing received data.
     */
    static size_t curlCallback(char* contents, size_t size, size_t nmemb, std::string* s);
};

#endif // !PageLoader_hpp
