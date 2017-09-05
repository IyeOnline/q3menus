#pragma once

#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <exception>
#include <regex>
#include <iomanip>
#include <ctime>

#include "RX.h"
#include "types.h"
#include "item.h"
#include "debug.h"
#include "stringmanip.h"


namespace q3menus
{
	class menu
	{
		public:
		//general
			std::string name = "UNNAMED";
			bool fullscreen = true;
			rectType rect;
			std::string type = "";
		//style
			std::string style = "1";
			int border = 0;
			color backcolor;
			color forecolor;
			color bordercolor;
			color focuscolor;
			bool visible = true;
			std::string background = "";
		//action
			std::string onOpen = "";
			std::string onClose = "";
			std::string onESC = "";
		//items
			std::list<item> items;
			std::vector<std::string> assetGlobalDef;
			std::vector<std::string> headComment;
			
		//io functions
			void ParseLine(const std::string& line);
			void ParseIntoMenu(const std::string& s);
			const bool readFromFile(const std::string& filename);
			const bool writeToFile(const std::string& filename, const std::string indentString="\t", const bool meta=true);


		//utilities
			const size_t itemCount() const { return items.size(); }; 
			void moveItems( const int dx , const int dy );
			void addItems(const std::list<item>& l);
			int removeItemsByProperty(std::function<bool(const item&)> lambda);
			std::list<item*> getItemsByProperty(std::function<bool(const item&)> lambda);
	};

	using fm = std::function<void(menu&,cSr)>; 
	
	//map connecting RX and the action that should be applied if RX matches
	const std::list< std::pair<cRXr,fm> > RX_MENU_MAP = {
		{ RX_name,[](menu& i,cSr s){i.name=s;} },
		{ RX_background,[](menu& i, cSr s){i.background=s;} },
		{ RX_fullscreen,[](menu& i, cSr s){i.fullscreen=(s.find("0")==std::string::npos?true:false);} },
		{ RX_rect,[](menu& i, cSr s){i.rect=rectType(vstovi(strmanip::split(s)));} },
		{ RX_border,[](menu& i, cSr s){i.border=std::stoi(s);} },
		{ RX_forecolor,[](menu& i, cSr s){i.forecolor=color(vstovd(strmanip::split(s,4)));} },
		{ RX_backcolor,[](menu& i, cSr s){i.backcolor=color(vstovd(strmanip::split(s,4)));} },
		{ RX_bordercolor,[](menu& i, cSr s){i.bordercolor=color(vstovd(strmanip::split(s,4)));} },
		{ RX_focuscolor,[](menu& i, cSr s){i.focuscolor=color(vstovd(strmanip::split(s,4)));} },
		{ RX_visible,[](menu& i, cSr s){i.visible=(s.find("0")==std::string::npos?true:false);} },
		{ RX_onOpen,[](menu& i, cSr s){i.onOpen=strmanip::trim(s);} },
		{ RX_onClose,[](menu& i, cSr s){i.onClose=strmanip::trim(s);} },
		{ RX_onESC,[](menu& i, cSr s){i.onESC=strmanip::trim(s);} },
		{ RX_type,[](menu& i, cSr s){i.type=s;} },
		{ RX_style,[](menu& i, cSr s){i.style=s;} },
	};
}

// kate: space-indent off; replace-tabs off
