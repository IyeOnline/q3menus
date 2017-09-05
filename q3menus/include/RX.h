#pragma once
#include <regex>
#include <exception>
#include <string>
#include <list>
#include <utility>
#include <functional>
#include <tuple>

#include "debug.h"
#include "stringmanip.h"

namespace q3menus
{
	//FUNCTIONS
	void RX_fixNewlines(std::string& str); //changes all newlines to \n
	const std::string RX_remove(const std::string& str,const std::regex& rx); //removes all newline chars
	bool RX_PARSE(std::string& str,std::regex rx); //if rx matches str, modifies str to only contain match[1]
	bool RX_CHECK(std::string& str,std::regex rx); //checks if rx matches str
	std::pair<const bool,const std::string> RX_ADV_PARSE( const std::string& str,const std::regex rx); //returns a bool and match[1] depending on if rx matches str
	const std::regex RX_ASSEMBLE( const std::string& rx_prototype, const std::string& catchword, const bool lf=true, const bool icase=true); //builds a RX
  
	//constants
// 	const std::string decimalmask = "((\\d+(\\.\\d{1,5})?)|(\\.\\d{1,5}))"; //5 digit accurate decimals, accepts: 1 ; 1.1; .1; schemes
	const std::string delimiters = "[\\s\\t]"; //exactly one delimeter
	const std::string delA = delimiters + "+"; //at least one delimeter
	const std::string delB = delimiters + "*"; //any number of delimeters
	const std::string newline = "[\\r\\n?|\\n]"; //newline that should work with both win and linux endings
	const std::string nl0 = newline + "?"; //zero or one newlines
	const std::string nlA = newline + "+"; //at least one newline
	const std::string nlB = newline + "*"; //any number of newlines
	
	//proto RX
	const std::string RX_proto_quoted = "\"([^\"]+)\""; 
	const std::string RX_proto_brackets = "\\{"+delB+"([^\\}\\{]+)"+delB+"\\}";
// 	const std::string RX_proto_layeredBrackets = "\\{(.*)\\}";
// 	const std::string RX_proto_string = "\"?([^\"]+)\"?";
// 	const std::string RX_proto_string = "(\"[^\"]+\"|[^\"\\n\\s]+)";
	const std::string RX_proto_string = "(\"([^\"]+)\"|(\\w+))";
	const std::string RX_proto_digit = "([\\d\\.]+)";
	const std::string RX_proto_4floats = "([\\d\\.]+" + delA + "[\\d\\.]+" + delA + "[\\d\\.]+" + delA + "[\\d\\.]+)";
	const std::string RX_proto_4ints = "([\\d\\-]+" + delA + "[\\d\\-]+" + delA + "[\\d\\-]+" + delA + "[\\d\\-]+)";
// 	const std::string RX_proto_number = "([\\d\\.]+)";
	
	//blocks
	const std::regex RX_itemDef_open(delB + "itemDef" + delB + nl0 + delB + "\\{",std::regex_constants::icase);
	const std::regex RX_assetGlobalDef_open(delB + "assetGlobalDef" + delB + nl0 + delB + "\\{",std::regex_constants::icase);
	const std::regex RX_menuDef_open(delB + "menuDef" + delB + nl0 + delB + "\\{",std::regex_constants::icase);
// 	const std::regex RX_itemDef_full(delB + "itemDef" + delB + RX_proto_layeredBrackets,std::regex_constants::icase);
	const std::regex RX_commentLine("\\W*//.*");
// 	const std::regex RX_menuhead("menuDef[\\s\\t\\{(\\.*)itemDef]*",std::regex_constants::icase);
	
	//"" encapsulated
	const std::regex RX_name(delB + "name" + delA + RX_proto_string,std::regex_constants::icase);
	const std::regex RX_group(delB + "group" + delA + RX_proto_string,std::regex_constants::icase);
	const std::regex RX_cvartest(delB + "cvartest" + delA + RX_proto_string,std::regex_constants::icase);
	const std::regex RX_background(delB + "background" + delA + RX_proto_quoted/**/,std::regex_constants::icase);
	const std::regex RX_text(delB + "text" + delA + RX_proto_quoted,std::regex_constants::icase);
	const std::regex RX_onlyquoted("[^\\w/]" + delimiters + "{2,}" + RX_proto_quoted); //used to find any further texts when wrapped text is encountered
	
	//single numbers
	const std::regex RX_fullscreen(delB + "fullScreen" + delA + RX_proto_digit,std::regex_constants::icase);
	const std::regex RX_visible(delB + "visible" + delA + RX_proto_digit,std::regex_constants::icase);
	const std::regex RX_border(delB + "border" + delA + RX_proto_digit,std::regex_constants::icase);
	const std::regex RX_textalignX(delB + "textalignX" + delA + RX_proto_digit,std::regex_constants::icase);
	const std::regex RX_textalignY(delB + "textalignY" + delA + RX_proto_digit,std::regex_constants::icase);
	const std::regex RX_textscale(delB + "textscale" + delA + RX_proto_digit,std::regex_constants::icase);
	
	//number or string
	const std::regex RX_type(delB + "type" + delA + RX_proto_string,std::regex_constants::icase);
	const std::regex RX_style(delB + "style" + delA + RX_proto_string,std::regex_constants::icase);
	const std::regex RX_textalign(delB + "textalign" + delA + RX_proto_string,std::regex_constants::icase);
	
	//keywords
	const std::regex RX_decoration(delB + "decoration",std::regex_constants::icase);
	const std::regex RX_wrapped(delB + "wrapped",std::regex_constants::icase);
	
	
	// 4 value
	const std::regex RX_rect(delB + "rect" + delA + RX_proto_4ints,std::regex_constants::icase);
	const std::regex RX_forecolor(delB + "forecolor" + delA + RX_proto_4floats,std::regex_constants::icase);
	const std::regex RX_backcolor(delB + "backcolor" + delA + RX_proto_4floats,std::regex_constants::icase);
	const std::regex RX_bordercolor(delB + "bordercolor" + delA + RX_proto_4floats,std::regex_constants::icase);
	const std::regex RX_focuscolor(delB + "focuscolor" + delA + RX_proto_4floats,std::regex_constants::icase);
	
	// {} encapsulated
	const std::regex RX_onOpen(delB + "onOpen" + delA + RX_proto_brackets,std::regex_constants::icase);
	const std::regex RX_onClose(delB + "onClose" + delA + RX_proto_brackets,std::regex_constants::icase);
	const std::regex RX_onESC(delB + "onESC" + delA + RX_proto_brackets,std::regex_constants::icase);
	
	const std::regex RX_hideCvar(delB + "hideCvar" + delA + RX_proto_brackets,std::regex_constants::icase);
	const std::regex RX_showCvar(delB + "showCvar" + delA + RX_proto_brackets,std::regex_constants::icase);
	const std::regex RX_disableCvar(delB + "disableCvar" + delA + RX_proto_brackets,std::regex_constants::icase);
	const std::regex RX_enableCvar(delB + "enableCvar" + delA + RX_proto_brackets,std::regex_constants::icase);
	
	const std::regex RX_action(delB + "action" + delA + RX_proto_brackets,std::regex_constants::icase);
	const std::regex RX_mouseEnter(delB + "mouseEnter" + delA + RX_proto_brackets,std::regex_constants::icase);
	const std::regex RX_mouseExit(delB + "mouseExit" + delA + RX_proto_brackets,std::regex_constants::icase);
}

// kate: space-indent off; replace-tabs off
