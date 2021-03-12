#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

#include <gumbo.h>
#include "PageLoader/PageLoader.hpp"
#include "Parser/Parser.hpp"

int main() {
    std::string url = "https://rau.am";
    PageLoader pL;
    Page res = pL.load(url);
    
    Parser parser(res.getUrl(), res.getBody());
    
    parser.parse();

//    for (const std::string& u : parser.getUrls()) {
//        std::cout << u << std::endl;
//    }
    
}
