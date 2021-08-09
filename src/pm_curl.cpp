#include "pm_curl.h"

size_t PM_Curl::CurlDataWrite(void* buf, size_t size, size_t nmemb, void* userp)
{
	if(userp)
	{
		ostream& os = *static_cast<ostream*>(userp);
		streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(buf), len))
			return len;
	}
	else
		cout << "Failed to write data" << endl;
	
	
	return 0;
}

CURLcode PM_Curl::CurlGet(const std::string &l_strURL, std::ostream &os){
	CURLcode code;
	CURL* curl = curl_easy_init();
	if (curl) 
	{
		if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlDataWrite)) && 
		CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_HEADER, 0)) &&
		CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false)) &&
		CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_USERPWD, "")) &&
		CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os)) &&
		CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30)) &&
		CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, l_strURL.c_str())))
		{
			code = curl_easy_perform(curl);
		}
		
		curl_easy_reset(curl);
		curl_easy_cleanup(curl);
	}
	else
		cout << "Failed to initialize curl object" << endl;
	
	return code;
}
