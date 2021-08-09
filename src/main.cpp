#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>
#include <sstream>
#include <fstream>
#include <thread>
#include <map>
#include "pm_curl.h"
#include "Util.h"

using namespace std;
enum ReturnType
{
	FAILURE,
	SUCCESS
};
typedef unsigned short u16;
typedef unsigned int u32;

int main()
{
	ostringstream oss;
	std::multimap<u32, std::string> l_mmNoToURL_Price;
	typedef std::multimap<u32, std::string>::iterator MMIter;
	l_mmNoToURL_Price.insert(std::pair<u32,std::string> (8865924123,"https://www.amazon.in/gp/product/B086WM3RB8/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1|2,499"));
	l_mmNoToURL_Price.insert(std::pair<u32,std::string> (8865924123,"https://www.amazon.in/Bar-Wireless-Bluetooth-Soundbar-Subwoofer/dp/B07FPLKKCS/ref=sr_1_2?dchild=1&keywords=soundbar+with+woofer&qid=1617191644&s=kitchen&sr=1-2|7,999"));
	
	while(true)
	{
		for(MMIter itr = l_mmNoToURL_Price.begin(); itr != l_mmNoToURL_Price.end(); itr++)
		{	
			std::string l_strURL_Price = itr->second;
			
			if(CURLE_OK == PM_Curl::CurlGet("https://www.amazon.in/gp/product/B086WM3RB8/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1", oss))
			{
				cout << "successfully hit api" <<endl;
				
				std::istringstream f(oss.str());
				std::string line;   
				std::string price;
				while (std::getline(f, line)) 
				{	
					if(line.find("priceBlockBuyingPriceString") != string::npos)
					{
						cout << line << endl;
						int price_start 	= line.find("\">");
						int price_end		= line.find("<", price_start);
						
						int length 	= price_end - (price_start + 5);
						
						price = line.substr(price_start + 5, length);
						break;
					}
					if(line.find("priceBlockDealPriceString") != string::npos)
					{
						cout << line << endl;
						int price_start 	= line.find("\">");
						int price_end		= line.find("<", price_start);
						
						int length 	= price_end - (price_start + 5);
						price = line.substr(price_start + 5, length);
						break;
					}
				}
				cout << "price : " << price << endl;
				ofstream ofs;
				ofs.open("price.txt",std::ios_base::app);
				ofs << price << "\n";
			}
			else
				cout << "Failed to hit api .." << endl;
		}
		std::this_thread::sleep_for (std::chrono::hours(1));
	}
		
	return 0;
}