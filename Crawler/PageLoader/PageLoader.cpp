#include "PageLoader.hpp"

#include <stdio.h>
#include <curl/curl.h>
#include <iostream>

PageLoader::PageLoader() {
    
}

Page PageLoader::load(const std::string& url) {
    CURL* curl;
    CURLcode res;
    
    std::string s;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    
    return Page(s);
}

size_t PageLoader::CurlWrite_CallbackFunc_StdString(void* contents, size_t size, size_t nmemb, std::string* s) {
   size_t newLength = size * nmemb;
   try {
       s->append((char*)contents, newLength);
   } catch(std::bad_alloc &e) {
       //handle memory problem
       return 0;
   }
   return newLength;
}
