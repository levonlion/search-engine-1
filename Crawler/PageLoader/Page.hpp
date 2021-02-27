#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>

class Page {
    
private:
    
    std::string body;
    int status;

public:
    
    Page(const std::string&);
    
    int isError() const;
    const std::string& getBody() const;
    int getStatus() const;
};

#endif // !PAGE_HPP
