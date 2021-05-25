#include "PageLoader.hpp"

#include <stdio.h>
#include <curl/curl.h>
#include <iostream>

Page PageLoader::load(const std::string& url) {
    CURL* curl = curl_easy_init();
    
    // The initial value is for internal use only, will never be returned by libcurl.
    CURLcode requestResult = CURLE_NO_CONNECTION_AVAILABLE;
    
    std::string data;
    
    // The initial value of 0 means that no server response code has been received.
    Page::statusType responseCode = 0;
    
    std::string effectiveUrl;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        /* enable redirect following */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        /* allow three redirects */
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        
        struct curl_slist* list = NULL;
        list = curl_slist_append(list, "Accept: text/html");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        
        // Performs the request.
        requestResult = curl_easy_perform(curl);
        
        curl_slist_free_all(list);
        
        // Check for errors.
        if(requestResult != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(requestResult));
        } else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
            
            char* url = nullptr;
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
            
            if (url != nullptr) {
                effectiveUrl.append(url);
            }
            
            char* ct = nullptr;
            int res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
            if(!res && ct) {
                if (std::string(ct).find("text/html") == std::string::npos) {
                    responseCode = 406;
                }
            }
        }
        
        // Always cleanup.
        curl_easy_cleanup(curl);
    }
    return Page(effectiveUrl, data, responseCode, requestResult);
}

size_t PageLoader::curlCallback(char* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    
    s->append(contents, newLength);
    
    return newLength;
}
