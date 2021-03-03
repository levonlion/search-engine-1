#ifndef PAGE_LOADER_HPP
#define PAGE_LOADER_HPP

#include <string>
#include "Page.hpp"

class PageLoader {
    
public:
    
    PageLoader();

    Page load(const std::string& url);
    
private:
    
    static size_t CurlWrite_CallbackFunc_StdString(char* contents, size_t size, size_t nmemb, std::string* s);
};

#endif // !PAGE_LOADER_HPP
