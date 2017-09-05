#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <utility>

namespace strmanip
{
	//splits a string at char delim, into a vector. Reserves N items for the split to improve performance when called on known strings.
	const std::vector<std::string> split(const std::string &s, const size_t N=0, const char delim=' ');
	
	//turns a double into a string, rounded to decDigits
	const std::string prd(const double x, const int decDigits);
	
	//trins a string of any leading and tailing spaces, tabs and newlines
	const std::string trim(const std::string& str, const std::string& whitespace = " \t\n\r"); 
	
	//removes any comments from str
	void removeComment(std::string& str); 
	
	//removes any leading tabs and spaces, as well as comments
	void filterLine(std::string& str); 
}
