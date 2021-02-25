#ifndef PAGE_LOADER_HPP
#define PAGE_LOADER_HPP

#include <string>
#include "Page.hpp"

class PageLoader {
public:
    PageLoader();

    //libcurl 
    Page load(const std::string& url);
};
#endif // !PAGE_LOADER_HPP
