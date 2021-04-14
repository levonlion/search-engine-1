#ifndef Document_hpp
#define Document_hpp

#include <string>

class Document {
    
private:
    
    std::string url;
    std::string title;
    std::string description;
    std::string allText;
    
public:
    
    Document() = default;
    
    Document(const std::string& url, const std::string& title, const std::string& description, const std::string& allText);
    
    const std::string& getUrl() const;
    
    const std::string& getTitle() const;
    
    const std::string& getDescription() const;
    
    const std::string& getAllText() const;
};


#endif /* Document_hpp */
