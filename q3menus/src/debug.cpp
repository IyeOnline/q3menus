#include "debug.h"

namespace q3menus
{
	void debug(const size_t treshhold,std::string name, const std::string& text)
	{
		if(treshhold <= debuglevel)
		{
			std::transform(name.begin(), name.end(),name.begin(), ::toupper);
			std::cout << "\tDEBUG:" << name << ": " << text << std::endl;
		}
	}
}

// kate: space-indent off; replace-tabs off