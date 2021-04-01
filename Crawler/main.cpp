#include <iostream>
#include "WebsiteStore/WebsiteStore.hpp"
#include "LinkStore/LinkStore.hpp"
#include "PageLoader/PageLoader.hpp"
#include "Parser/Parser.hpp"

int main() {
    WebsiteStore websiteStore;
//    websiteStore.add(Website("rau.am", "https://rau.am", 0));
    websiteStore.add(Website("macrumors.com", "https://www.macrumors.com", 0));
    const auto& websites = websiteStore.getAll();
    
    LinkStore linkStore;
    PageLoader pageLoader;
    for (const auto& website : websites) {
        
//        if (website.getLastCrawlingTime() + someUpdateInterval > time(NUll)) {
//            continue;
//        }
        
        const auto& homepageLink = linkStore.getBy(website.getHomepage());
        
        if (homepageLink.has_value()) {
            linkStore.update(Link(website.getHomepage(), website.getDomain(), LinkStatus::WAITING, homepageLink.value().getLastLoadTime()));
        } else {
            linkStore.add(Link(website.getHomepage(), website.getDomain(), LinkStatus::WAITING, 0));
        }
        
        while (true) {
            const auto& links = linkStore.getBy(website.getDomain(), LinkStatus::WAITING, 10);
            
            if (links.empty()) {
                break;
            }
            
            for (const auto& link : links) {
                const auto& page = pageLoader.load(link.getUrl());
                if (page.isError() || page.getStatus() < 200 ||  page.getStatus() >= 300) {
                    linkStore.update(Link(link.getUrl(), link.getDomain(), LinkStatus::ERROR, time(NULL)));
                    continue;
                }
                
                Parser parser(page.getUrl(), page.getBody());
                
                parser.parse();
                
                for (const std::string& u : parser.getUrls()) {
                    std::cout << u << std::endl;
                }
                
                // create document from parser and save
                
                for (const auto& newUrl : parser.getUrls()) {
                    if (linkStore.getBy(newUrl).has_value()) {
                        continue;
                    }
                    linkStore.update(Link(newUrl, website.getDomain(), LinkStatus::WAITING, time(NULL)));
                }
                
                linkStore.update(Link(link.getUrl(), link.getDomain(), LinkStatus::LOADED, time(NULL)));
            }
        }
    }
}

