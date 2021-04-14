#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include <vector>
#include <optional>
#include <functional>

#include <gumbo.h>

class Parser {
    
private:
    
    /**
     * The effective url.
     */
    std::string url;
    
    /**
     * The effective url host.
     */
    std::string urlHost;
    
    /**
     * The effective url path.
     */
    std::string urlPath;
    
    /**
     * The effective url scheme.
     */
    std::string urlScheme;
    
    /**
     * The entire HTML document.
     */
    std::string html;
    
    /**
     * All urls.
     */
    std::vector<std::string> urls;
    
    /**
     * Title inside <head>.
     */
    std::string title;
    
    /**
     * Content of the content attribute of <meta name="description" content="Some content">
     */
    std::string description;
    
    /**
     * All clean text.
     */
    std::string allText;
    
private:

    /**
     * Extract all urls.
     */
    void extractUrls(GumboNode* node);
    
    /**
     * Extracts clean text.
     */
    std::string extractCleanText(GumboNode* node) const;
    
    /**
     * Extracts title tag content of the head tag.
     */
    std::string extractTitle(const GumboNode* root) const;
    
    /**
     * Extract content of the content attribute of <meta name="description" content="Some content">
     */
    void extractDescription(GumboNode* node);
    
    /**
     * @return The scheme of url.
     */
    static std::optional<std::string> scheme(const std::string& url);
    
    /**
     * @return The host of url.
     */
    static std::optional<std::string> host(const std::string& url);
    
    /**
     * @return The path of url.
     */
    static std::optional<std::string> path(const std::string& url);

public:
    
    /**
     * Parse the HTML document.
     * @param url The effective url.
     * @param html The entire HTML document.
     */
    Parser(const std::string& url, const std::string& html);
    
    /**
     * Parse the HTML document.
     */
    void parse();
    
    /**
     * @return All urls.
     */
    const std::vector<std::string>& getUrls() const;
    
    /**
     * @return Title tag content of the head tag.
     */
    const std::string& getTitle() const;
    
    /**
     * @return Content of the content attribute of <meta name="description" content="Some content">
     */
    const std::string& getDescription() const;
    
    /**
     * @return All clean text.
     */
    const std::string& getAllText() const;
};

#endif /* Parser_hpp */
