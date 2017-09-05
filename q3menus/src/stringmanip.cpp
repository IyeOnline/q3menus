#include "stringmanip.h"

namespace strmanip
{
	const std::vector<std::string> split(const std::string &s, const size_t N, const char delim) 
	{
		std::stringstream ss(s);
		std::string cs;
		std::vector<std::string> result;
		result.reserve(N);
		while (std::getline(ss, cs, delim)) 
		{
			if(!cs.empty())
				result.push_back(cs);
		}
		return result;
	}
	
	const std::string prd(const double x, const int decDigits) 
	{
		std::stringstream ss;
		ss << std::fixed;
		ss.precision(decDigits); // set # places after decimal
		ss << x;
		return ss.str();
	}

	const std::string trim(const std::string& str, const std::string& whitespace)
	{
		const auto strBegin = str.find_first_not_of(whitespace);
		if (strBegin == std::string::npos)
			return ""; // no content

		const auto strEnd = str.find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}
	
	void removeComment(std::string& str)
	{
		const auto pos = str.find("//");
		if( pos != std::string::npos)
		{
			str = str.substr(0,pos);
		}
	}
	
	void filterLine(std::string& str)
	{
		str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
		removeComment(str);
	}
}
