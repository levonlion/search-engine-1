#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>
#include <curl/curl.h>

class Page {
    
public:
    
    typedef long statusType;
    typedef CURLcode errorType;
    
private:
    
    /**
     * The entire HTML document.
     */
    std::string body;
    
    /**
     * The HTTP, FTP or SMTP response code.
     */
    statusType status;

    /**
     * The return value of the entire request.
     */
    errorType error;

public:
    
    /**
     * Creates a page with a given body, status and error.
     * @param body The entire HTML document.
     * @param status The HTTP, FTP or SMTP response code.
     * @param error The return value of the entire request.
     */
    Page(const std::string& body, statusType status, errorType error);
    
    /**
     * @return The entire request value.
     */
    errorType isError() const;
    
    /**
     * @return The entire HTML document.
     */
    const std::string& getBody() const;
    
    /**
     * @return The HTTP, FTP or SMTP response code.
     */
    statusType getStatus() const;
};

#endif // !PAGE_HPP
