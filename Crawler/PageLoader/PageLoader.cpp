#include "PageLoader.hpp"

#include <stdio.h>
#include <curl/curl.h>
#include <iostream>

PageLoader::PageLoader() {
    
}

Page PageLoader::load(const std::string& url) {
    CURL* curl = curl_easy_init();
    
    // The initial value is for internal use only, will never be returned by libcurl.
    CURLcode requestResult = CURLE_NO_CONNECTION_AVAILABLE;
    
    std::string data;
    
    // The initial value of 0 means that no server response code has been received.
    Page::statusType responseCode = 0;
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        
        // Perform the request, res will get the return code.
        requestResult = curl_easy_perform(curl);
        
        // Check for errors.
        if(requestResult != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(requestResult));
        } else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        }
        
        // Always cleanup.
        curl_easy_cleanup(curl);
    }
    
    return Page(data, responseCode, requestResult);
}

size_t PageLoader::curlCallback(char* contents, size_t size, size_t nmemb, std::string* s) {
   size_t newLength = size * nmemb;
   try {
       s->append(contents, newLength);
   } catch(std::bad_alloc &e) {
       std::cerr <<  "memory problem" << std::endl;
       return 0;
   }
   return newLength;
}
