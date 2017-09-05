#include "item.h"

namespace q3menus
{
	const std::string item::returndef(const std::string indentString, const size_t N) const
	{
		std::string fulldef;
		std::string newline = "\n";
		for(size_t i = 0 ; i <= N ; ++i) newline += indentString;
		
		
		if(!headcomment.empty()) 
		{
			for(size_t i = 0 ; i < N ; ++i) fulldef += indentString;
			fulldef += "\\*" + headcomment + "\\*\n";
		}
		for(size_t i = 0 ; i < N ; ++i) fulldef += indentString;
		fulldef += "itemDef {";
		fulldef += newline + "name \"" + name + "\"";
		if(!group.empty()) { newline + fulldef += "group \"" +  group + "\""; }
		fulldef += newline + rect.getrectstring();
		if(!type.empty()) { fulldef += newline + "type " + type; }
		if(!style.empty()) { fulldef += newline + "style " + style; }
		if(!background.empty()) { fulldef += newline + "background \"" + background + "\""; }
		fulldef += newline + "border " + (border?"1":"0");
		if(!backcolor.isEmpty) fulldef += newline + "backcolor " + backcolor.getcolorstring();
		if(!forecolor.isEmpty) fulldef += newline + "forecolor " + forecolor.getcolorstring();
		if(border && !bordercolor.isEmpty) fulldef += newline + "bordercolor " + bordercolor.getcolorstring();
		fulldef += newline + "visible " + std::to_string(visible);
		if (decoration) 
		{ 
			fulldef += newline + "decoration"; 
		}
		if(!cvarTest.empty())
		{
			fulldef += newline + "cvarTest \"" + cvarTest + "\"";
			if(!hideCvar.empty())
				fulldef += newline + "hideCvar { " + hideCvar + " }";
			if(!showCvar.empty())
				fulldef += newline + "showCvar { " + showCvar + " }";
			if(!disableCvar.empty())
				fulldef += newline + "disableCvar { " + disableCvar + " }";
			if(!enableCvar.empty())
				fulldef += newline + "enableCvar { " + enableCvar + " }";
		}
		if (!text.empty()) 
		{
			fulldef += newline + "textalign " + textalign;
			fulldef += newline + "textalignx " + std::to_string(textalignX);
			fulldef += newline + "textaligny " + std::to_string(textalignY);
			fulldef += newline + "textscale " + std::to_string(textscale);
			if(wrapped||text.size()>1)
			{
				fulldef += newline + "wrapped";
				if(!text[0].empty()) fulldef += newline + "text \"" + text[0] + "\\r\"";
				for( size_t i = 1 ; i < text.size() ; ++i )
				{
					if(!text[i].empty()) fulldef += newline + "\"" + text[i] + "\\r\"";
				}
			}
			else
			{
				if(!text[0].empty()) fulldef += newline + "text \"" + text[0] + "\"";
			}
		}
		if (!action.empty())
		{ 
			const bool ml = action.find("\n") == std::string::npos;
			const std::string mls = (ml?"":newline+indentString);
			fulldef += newline + "action { " + mls + action + mls + " }"; 
		}
		if (!mouseEnter.empty())
		{ 
			const bool ml = mouseEnter.find("\n") == std::string::npos;
			const std::string mls = (ml?"":newline+indentString);
			fulldef += newline + "mouseEnter { " + mls + mouseEnter + mls + " }"; 
		}
		if (!mouseExit.empty())
		{ 
			const bool ml = mouseExit.find("\n") == std::string::npos;
			const std::string mls = (ml?"":newline+indentString);
			fulldef += newline + "mouseExit { " + mls + mouseExit + mls + " }"; 
		}
		fulldef += "\n";
		for(size_t i = 0 ; i < N ; ++i) fulldef += indentString;
		
		fulldef += "}\n";
		return fulldef;
	}

	void item::init_general(const std::string& name_arg, const std::string& group_arg, const rectType rectvalue_arg, const std::string& type_arg)
	{
		name = name_arg;
		group = group_arg;
		rect = rectvalue_arg;
		type = type_arg;
	}
	
	void item::init_activity( const std::string& cvarTest_arg, const std::string& hideCvar_arg, const std::string& showCvar_arg, const std::string& disableCvar_arg, std::string& enableCvar_arg)
	{
		cvarTest = cvarTest_arg;
		hideCvar = hideCvar_arg;
		showCvar = showCvar_arg;
		disableCvar = disableCvar_arg;
		enableCvar = enableCvar_arg;
	}
	
	void item::init_style( const std::string& style_arg,const int border_arg,const color backcolor_arg,const color forecolor_arg,const color bordercolor_arg,const color focuscolor_arg,const bool visible_arg, const bool decoration_arg)
	{
		style = style_arg;
		border = border_arg;
		backcolor = backcolor_arg;
		forecolor = forecolor_arg;
		bordercolor = bordercolor_arg;
		focuscolor = focuscolor_arg;
		visible = visible_arg;
		decoration = decoration_arg;
	}
	
	void item::init_text( const std::string& text_arg, const std::string& textalign_arg, const int textalignX_arg, const int textalignY_arg, const double textscale_arg)
	{
		text.clear();
		text.push_back(text_arg);
		textalign = textalign_arg;
		textalignX = textalignX_arg;
		textalignY = textalignY_arg;
		textscale = textscale_arg;
	}
	
	void item::init_text(const std::vector<std::string>& text_arg, const std::string textalign_arg, const int textalignX_arg, const int textalignY_arg, const double textscale_arg)
	{
		text = text_arg;
		textalign = textalign_arg;
		textalignX = textalignX_arg;
		textalignY = textalignY_arg;
		textscale = textscale_arg;
	}
	
	void item::init_interaction(const std::string& action_arg, const std::string& mouseEnter_arg, const std::string& mouseExit_arg)
	{
		action = action_arg;
		mouseEnter = mouseEnter_arg;
		mouseExit = mouseExit_arg;
	}
	
	const item ParseItem(const std::string& itemtext)
	{
		debug(5,"parseitem","itemtext [[" + itemtext + " ]]");
		item result;
		int count = 0;
		for(const auto& k : RX_ITEM_MAP )
		{
			debug(5,"parseitem","testing RX #"+ (std::to_string(++count)));
			const auto x = RX_ADV_PARSE(itemtext,k.first);
			if(x.first)
			{
				k.second(result,x.second);
			}
		}
		if(!result.text.empty()||result.wrapped) //support for multiline text
		{
			debug(5,"parseitem","found wrapped or non empty text. trying to catch further text...");
			std::smatch m;
			std::string::const_iterator searchStart( itemtext.cbegin() );
			while ( std::regex_search( searchStart, itemtext.cend(), m, RX_onlyquoted ) )
			{
				const std::string s = removeLiteralNewlines(strmanip::trim(m[1]));
				debug(5,"parseitem","assuming [[" + s + "]] is further text");
				result.text.push_back(s);
				searchStart += m.position() + m.length();
			}
		}
		
		return result;
	}
	
	
	const std::list<item> ParseItems(std::ifstream& ifs,bool initem,int bracketcounter,std::string itemtext)
	{
		std::string line;
// 		std::string itemtext = leftover;
		std::list<item> items;
// 		int bracketcounter =1; //we already skipped the itemDef line
		size_t itemcounter = 0;
// 		bool initem = true;//we already skipped the itemDef line
		while(std::getline(ifs, line))
		{
			strmanip::removeComment(line);
			RX_fixNewlines(line);
			itemtext += line;
			if( !initem && std::regex_search(itemtext,RX_itemDef_open))
			{
				itemtext = line;
				initem = true;
				++bracketcounter;
			}
			else if(line.find("{") !=std::string::npos )
				++bracketcounter;
			if(line.find("}") !=std::string::npos )
				--bracketcounter;
				
			if( bracketcounter < 0 )
			{
				break;
			}
			else if( initem && bracketcounter == 0 )	
			{
				items.push_back(ParseItem(itemtext));
				itemtext.clear();
				initem = false;
				bracketcounter = 0;
				debug(3,"read","item " + std::to_string(++itemcounter) + " parsed");
			}
			
			debug(4,"read",std::to_string(bracketcounter) + " braces open. initem: " + std::to_string(initem));
			debug(6,"read","current itemtext [[ " + itemtext + " ]]");
		}
		return items;
	}
	
	const std::string removeLiteralNewlines(const std::string& s)
	{
		
		return std::regex_replace(s, std::regex("\\\\r"),"");
	}
	
}

// kate: space-indent off; replace-tabs off
