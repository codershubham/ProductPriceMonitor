#include "util.h"

static std::vector<std::string> Util::SplitString(std::string f_strString, std::string f_strSeperator)
{
	std::vector<std::string> l_vecData;
	int index = 0;
	int prev_index = 0;
	while((index = f_strString.find(f_strSeperator)) != string::npos)
	{
		l_vecData = l_vecData.push_back(f_strString.substr(prev_index, index - prev_index));
		prev_index = index + 1;
	}
	
	return l_vecData;
}	
