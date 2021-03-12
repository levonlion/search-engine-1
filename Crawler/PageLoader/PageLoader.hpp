#ifndef Page_Loader_hpp
#define Page_Loader_hpp

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

#endif // !Page_Loader_hpp
