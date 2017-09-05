#include "RX.h"

namespace q3menus
{
	void RX_fixNewlines(std::string& str)
	{
// 		std::regex_replace(str.begin(),str.begin(), str.end(), std::regex(newline),"\n");
		std::regex_replace(str, std::regex(newline),"\n");
// 		std::regex_replace(str.begin(),str.begin(), str.end(), std::regex("\\r"),"\n");
// 		std::regex_replace(str.begin(),str.begin(), str.end(), std::regex("\\n\\n"),"\n");
	}
	
	const std::string RX_remove(const std::string& str,const std::regex& rx)
	{
		return std::regex_replace(str, rx,"");
	}
	
	bool RX_PARSE(std::string& str,std::regex rx)
	{
		debug(6,"RX_PARSE","called with [[" + str + "]]");
		std::smatch match;
		try
		{
			if (std::regex_match(str,match,rx))
			{
				str = match[1].str();
				debug(5,"RX_PARSE","match! Extracted: [[" + str + "]]");
				return true;
			}
		}
		catch (std::exception& e)
		{
			debug(0,"RX_PARSE",e.what());
		}
		debug(6,"RX_PARSE","no match!");
		return false;
	}

	bool RX_CHECK(std::string& str,std::regex rx)
	{
		debug(6,"RX_CHECK","called with [[" + str + "]]");
		try
		{
			if (std::regex_match(str,rx))
			{
				debug(6,"RX_CHECK","matches!");
				return true;
			}
		}
		catch (std::exception& e)
		{
			debug(0,"RX_PARSE",e.what());
		}
		debug(6,"RX_CHECK","no match!");
		return false;
	}
	
	/** @brief: checks STR for a regex constructed as [:spacing:]CATCHWORD:spacing:RX_PROTOTYPE ignoring case if ICASE */
	std::pair<const bool,const std::string> RX_ADV_PARSE(const std::string& str,const std::regex rx)
	{
		debug(6,"RX_ADV_PARSE","called with [[" + str + "]]");
		
		std::string resstr = "";
		bool result = false;
		
		try
		{
			std::smatch match;
			if(std::regex_search(str,match,rx))
			{
				if( (resstr = match[match.size()-1].str()).empty() )
					resstr = match[match.size()-2].str();
				debug(5,"RX_ADV_PARSE","match! Extracted: [[" + resstr + "]]");
				result = true;
			}
			else
				debug(6,"RX_ADV_PARSE","no match!");
		}
		catch(std::exception& e)
		{
			debug(0,"RX_ADV_PARSE",e.what());
		}
		
		
		return std::pair<bool,std::string>(result,resstr);
	}
	
	const std::regex RX_ASSEMBLE( const std::string& rx_prototype, const std::string& catchword, const bool lf, const bool icase)
	{
		const std::string s = delB + catchword + delA + rx_prototype + (lf?newline:"");
		debug(6,"RX_ASSEMBLE","RX construct: || " + s + " ||" + (icase?"ICASE":""));
		return std::regex( s ,std::regex_constants::extended|(icase? std::regex_constants::icase : std::regex_constants::extended) );;
	}
}

// kate: space-indent off; replace-tabs off
