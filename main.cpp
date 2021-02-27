#include <iostream>
#include "Crawler/PageLoader/PageLoader.hpp"

int main() {
    PageLoader pl;
    
    Page res = pl.load("curl.haxx.se");
    std::cout << res.getBody();
}
