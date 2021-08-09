#include <curl/curl.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class PM_Curl
{	
	public:
	static size_t CurlDataWrite(void* buf, size_t size, size_t nmemb, void* userp);
	static CURLcode CurlGet(const std::string &l_strURL, std::ostream &os);
};