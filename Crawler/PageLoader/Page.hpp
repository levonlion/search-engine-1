#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>

class Page {
    
private:
    
    std::string body;
    int status;

public:
    
    /**
     * Creates a page with a given body
     */
    Page(const std::string& body);
    
    int isError() const;
    
    const std::string& getBody() const;
    
    int getStatus() const;
};

#endif // !PAGE_HPP
