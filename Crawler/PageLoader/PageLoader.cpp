#include "PageLoader.hpp"

#include <stdio.h>
#include <curl/curl.h>
#include <iostream>

PageLoader::PageLoader() {
    
}

Page PageLoader::load(const std::string& url) {
    CURL* curl;
    
    // The initial value is for internal use only, will never be returned by libcurl
    CURLcode res = CURLE_NO_CONNECTION_AVAILABLE;
    
    std::string data;
    
    // The initial value of 0 means that no server response code has been received.
    Page::statusType responseCode = 0;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        
        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);
        
        // Check for errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        }
        
        // always cleanup
        curl_easy_cleanup(curl);
    }
    
    return Page(data, responseCode, res);
}

size_t PageLoader::CurlWrite_CallbackFunc_StdString(char* contents, size_t size, size_t nmemb, std::string* s) {
   size_t newLength = size * nmemb;
   try {
       s->append(contents, newLength);
   } catch(std::bad_alloc &e) {
       std::cerr <<  "memory problem" << std::endl;
       return 0;
   }
   return newLength;
}
