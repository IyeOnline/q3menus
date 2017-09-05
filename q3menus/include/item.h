#pragma once

#include <string>
#include <list>
#include <algorithm>
#include <regex>
#include <functional>
#include <list>
#include <fstream>

#include "types.h"
#include "RX.h"
#include "stringmanip.h"
#include "conversion.h"


namespace q3menus
{
	class item
	{
		public:
		//general
			std::string name = "UNNAMED";
			std::string group = "";
			rectType rect;
			std::string type = "1";
			std::string cvarTest = "";
			std::string hideCvar = "";
			std::string showCvar = "";
			std::string disableCvar = "";
			std::string enableCvar = "";
			std::string headcomment = "";
		//style
			std::string style = "1";
			int border = 1;
			color backcolor;
			color forecolor;
			color bordercolor;
			color focuscolor;
			bool visible = true;
			bool decoration = false;
			std::string background = "";
		//text
			std::vector<std::string> text;
			std::string textalign = "1";
			int textalignX = 0;
			int textalignY = 0;
			double textscale = .5;
			bool wrapped = false;
		//interactionstring
			std::string action = "";
			std::string mouseEnter = "";
			std::string mouseExit = "";
		//functions:
			item(void){};
			//returns a formated string for this item. the item will be indented N levels using indentString. terminated by a \n
			const std::string returndef(const std::string indentString, const size_t N) const;
			void init_general(const std::string& name_arg, const std::string& group_arg, const rectType rectvalue_arg, const std::string& type_arg);
			void init_activity( const std::string& cvarTest_arg, const std::string& hideCvar_arg, const std::string& showCvar_arg, const std::string& disableCvar_arg, std::string& enableCvar_arg);
			void init_style( const std::string& style_arg,const int border_arg,const color backcolor_arg,const color forecolor_arg,const color bordercolor_arg,const color focuscolor_arg,const bool visible_arg, const bool decoration_arg);
			void init_text( const std::string& text_arg, const std::string& textalign_arg, const int textalignX_arg, const int textalignY_arg, const double textscale_arg);
			void init_text(const std::vector<std::string>& text_arg, const std::string textalign_arg, const int textalignX_arg, const int textalignY_arg, const double textscale_arg);
			void init_interaction(const std::string& action_arg, const std::string& mouseEnter_arg, const std::string& mouseExit_arg);
	};
	
	const std::string removeLiteralNewlines(const std::string& s);
	
	const std::list<item> ParseItems(std::ifstream& ifs, bool initem=false, int bracketcounter=0,std::string itemtext="");
	const item ParseItem(const std::string& itemtext);
	
	template<typename T>
	//wraper around std::for_each, for ease of use
	void massTransform( std::list<item*> L , T lambda )
	{
		std::for_each(L.begin(),L.end(),lambda);
	}
	
	using fi = std::function<void(item&,cSr)>;
	//map connecting RX and the action that should be applied if RX matches
	const std::list< std::pair<cRXr,fi> > RX_ITEM_MAP = {
		{ RX_name,[](item& i, cSr s){i.name=s;} },
		{ RX_group,[](item& i, cSr s){i.group=s;} },
		{ RX_background,[](item& i, cSr s){i.background=s;} },
		{ RX_rect,[](item& i, cSr s){i.rect=rectType(vstovi(strmanip::split(s,4)));} },
		{ RX_cvartest,[](item& i, cSr s){i.cvarTest=s;} },
		{ RX_hideCvar,[](item& i, cSr s){i.hideCvar=s;} },
		{ RX_showCvar,[](item& i, cSr s){i.showCvar=s;} },
		{ RX_disableCvar,[](item& i, cSr s){i.disableCvar=s;} },
		{ RX_enableCvar,[](item& i, cSr s){i.enableCvar=s;} },
		{ RX_border,[](item& i, cSr s){i.border=std::stoi(s);} }, /*10*/
		{ RX_forecolor,[](item& i, cSr s){i.forecolor=color(vstovd(strmanip::split(s,4)));} }, 
		{ RX_backcolor,[](item& i, cSr s){i.backcolor=color(vstovd(strmanip::split(s,4)));} },
		{ RX_bordercolor,[](item& i, cSr s){i.bordercolor=color(vstovd(strmanip::split(s,4)));} },
		{ RX_focuscolor,[](item& i, cSr s){i.focuscolor=color(vstovd(strmanip::split(s,4)));} },
		{ RX_visible,[](item& i, cSr s){i.visible=(s.find("0")==std::string::npos?true:false);} },
		{ RX_decoration,[](item& i, cSr s){i.decoration=true; (void)s;} },
		{ RX_text,[](item& i, cSr s){i.text.push_back(removeLiteralNewlines(s));} },
		{ RX_textalign,[](item& i, cSr s){i.textalign=s;} },
		{ RX_textalignX,[](item& i, cSr s){i.textalignX=std::stoi(s);} },
		{ RX_textalignY,[](item& i, cSr s){i.textalignY=std::stoi(s);} },/*20*/
		{ RX_textscale,[](item& i, cSr s){i.textscale=std::stod(s);} },
		{ RX_action,[](item& i, cSr s){i.action=strmanip::trim(s);} },
		{ RX_mouseEnter,[](item& i, cSr s){i.mouseEnter=strmanip::trim(s);} },
		{ RX_mouseExit,[](item& i, cSr s){i.mouseExit=strmanip::trim(s);} },
		{ RX_commentLine,[](item& i, cSr s){i.headcomment=s;} },
		{ RX_wrapped,[](item& i, cSr s){i.wrapped=true; (void)s;} }
	};
}

// kate: space-indent off; replace-tabs off
