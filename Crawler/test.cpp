#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

#include <gumbo.h>
#include "PageLoader/PageLoader.hpp"
#include "Parser/Parser.hpp"

int main() {
    std::string url = "rau.am";
    PageLoader pL;
    Page res = pL.load(url);
    
    Parser parser(res.getUrl(), res.getBody());
    
    parser.parse();

    for (const std::string& u : parser.getUrls()) {
        std::cout << u << std::endl;
    }
    
    //TODO: Create a new module for inputting URLs (input is Website (for config))
    //TODO: Create a new module for updating pages after a while (save the time of the last update)
    
}
