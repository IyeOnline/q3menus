#include "conversion.h"

const std::vector<int> vstovi (const std::vector<std::string>& in)
{
	size_t l = in.size();
	std::vector<int> res(l);
	try
	{
		for(size_t i = 0 ; i < l ; i++)
			res[i] = std::stoi(in[i]);
	}
	catch(std::exception& e)
	{
		std::cout << "error in vstovi: " << e.what() << "\n";
		std::cout << "current input : |";
		for(const auto& x : in) std::cout << x << "|";
		std::cout << "\n";
		std::cout << "current outout: |";
		for(const auto& x : res) std::cout << x << "|" ;
		std::cout << "\n";
	}
	return res;
}

const std::vector<double> vstovd (const std::vector<std::string>& in)
{
	size_t l = in.size();
	std::vector<double> res(l);
	try
	{
		for(size_t i = 0 ; i < l ; i++)
			res[i] = std::stod(in[i]);
	}
	catch(std::exception& e)
	{
		std::cout << "error in vstovd: " << e.what() << "\n";
		std::cout << "current input : |";
		for(const auto& x : in) std::cout << x << "|";
		std::cout << "\n";
		std::cout << "current outout: |";
		for(const auto& x : res) std::cout << x << "|" ;
		std::cout << "\n";
	}
	return res;
}

// kate: space-indent off; replace-tabs off
