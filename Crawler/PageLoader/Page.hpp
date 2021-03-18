#ifndef Page_hpp
#define Page_hpp

#include <string>
#include <curl/curl.h>

class Page {
    
public:
    
    typedef long statusType;
    typedef CURLcode errorType;
    
private:
    
    /**
     * The effective url.
     */
    std::string url;
    
    /**
     * The entire HTML document.
     */
    std::string body;
    
    /**
     * The HTTP response code.
     */
    statusType status;

    /**
     * The return value of the entire request.
     */
    errorType error;

public:
    
    /**
     * Creates a page with a given body, status and error.
     * @param url The effective url.
     * @param body The entire HTML document.
     * @param status The HTTP response code.
     * @param error The return value of the entire request.
     */
    Page(const std::string& url, const std::string& body, statusType status, errorType error);
    
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
    
    /**
     * @return The effective url.
     */
    const std::string& getUrl() const;
};

#endif // !Page_hpp
