#include <iostream>
#include <ctime>
#include <memory>
#include "WebsiteStore/WebsiteStore.hpp"
#include "LinkStore/LinkStore.hpp"
#include "PageLoader/PageLoader.hpp"
#include "Parser/Parser.hpp"
#include "DocumentStore/DocumentStore.hpp"

int main() {
    std::shared_ptr<mysqlx::Client> client = std::make_shared<mysqlx::Client>("mysqlx://root:BD4bTxjlB9Jt@127.0.0.1:33060/Crawler");
    
    WebsiteStore websiteStore(client);
    const auto websites = websiteStore.getAll();
    
    LinkStore linkStore(client);
    DocumentStore documentStore(client);
    PageLoader pageLoader;
    for (const auto& website : websites) {
        
        if (website.getLastCrawlingTime() + 60 > std::time(nullptr)) {
            continue;
        }
        
        const auto homepageLink = linkStore.getBy(website.getHomepage());
        
        if (homepageLink.has_value()) {
            linkStore.update(Link(-1, website.getHomepage(), website.getDomain(), LinkStatus::WAITING, 0));
        } else {
            linkStore.add(Link(-1, website.getHomepage(), website.getDomain(), LinkStatus::WAITING, 0));
        }
        
        while (true) {
            const auto links = linkStore.getBy(website.getDomain(), LinkStatus::WAITING, 10);
            
            if (links.empty()) {
                break;
            }
            
            for (const auto& link : links) {
                const auto page = pageLoader.load(link.getUrl());
                if (page.isError() || page.getStatus() < 200 || page.getStatus() >= 300) {
                    linkStore.update(Link(link.getId(), link.getUrl(), link.getDomain(), LinkStatus::ERROR, std::time(nullptr)));
                    continue;
                }
                
                Parser parser(page.getUrl(), page.getBody());
                
                parser.parse();
                
                // create document from parser and save
                documentStore.save(Document(page.getUrl(), parser.getTitle(), parser.getDescription(), parser.getAllText()));
                
                for (const auto& newUrl : parser.getUrls()) {
                    if (linkStore.getBy(newUrl).has_value()) {
                        continue;
                    }
                    linkStore.add(Link(-1, newUrl, website.getDomain(), LinkStatus::WAITING, std::time(nullptr)));
                }
                
                linkStore.update(Link(-1, link.getUrl(), link.getDomain(), LinkStatus::LOADED, std::time(nullptr)));
                
                std::clog << "Documents: " << documentStore.count() << "\t" << "Links: " << linkStore.count() << std::endl;
            }
        }
        
        websiteStore.update(Website(website.getId(), website.getDomain(), website.getHomepage(), std::time(nullptr)));
    }
    
    client->close();
}
