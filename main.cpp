#include <iostream>
#include "Crawler/PageLoader/Page.hpp"

#include <stdio.h>
#include <curl/curl.h>

size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size * nmemb;
    try
    {
        s->append((char*)contents, newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }
    return newLength;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    std::string s;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "curl.haxx.se");
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
    
    std::cout << s << std::endl;
    return 0;
}

