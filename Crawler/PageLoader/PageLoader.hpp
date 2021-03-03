#ifndef PAGE_LOADER_HPP
#define PAGE_LOADER_HPP

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
    static size_t CurlWrite_CallbackFunc_StdString(char* contents, size_t size, size_t nmemb, std::string* s);
};

#endif // !PAGE_LOADER_HPP
