#include "menu.h"
#include "q3menus.h"

namespace q3menus
{
	const bool menu::readFromFile(const std::string& filename)
	{
		debug(1,"read","started!");
		std::ifstream infile;
		try
		{
			infile.open(filename);
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		if(!infile.is_open())
		{
			std::cout << "couldnt open file \"" + filename + "\". It probably doesnt exist.\n";
			return false;
		}
		
		std::string line;
		
		{
			debug(2,"read","entered head comment section");

			std::string headstring = "";
			bool menu = false;
			bool inassets = false;
			bool incomment = false;	
			while(std::getline(infile, line))
			{	
				debug(4,"read","comment current line = " + line);
				headstring += line;
				if(line.find("\\*")!=std::string::npos)
				{
					incomment = true;
				}
				else if(std::regex_search(line, RX_commentLine))
				{
					strmanip::removeComment(line);
					RX_fixNewlines(line);
					headComment.push_back(line);
				}
				else if(std::regex_search(headstring, RX_assetGlobalDef_open))
				{
					inassets = true;
					break;
				}
				else if(std::regex_search(headstring, RX_menuDef_open))
				{
					menu = true;
					break;
				}
				
				if(incomment)
				{	
					headComment.push_back(line);
					if(line.find("*\\")!=std::string::npos)
						break;
				}
				
			}
			
			if(inassets&&!menu)
			{
				debug(2,"read","entered assetGlobalDef section");
				while(std::getline(infile, line))
				{
					debug(4,"read","assets current line = " + line);
					if(line.find("}") != std::string::npos)
					{
						debug(3,"read","asset end found");
						inassets = false;
						break; //we are done with this getline.
					}
					else
					{
						debug(4,"read","asset continues");
						if(!line.empty())
							assetGlobalDef.push_back(line);
					}
				}
			}
		}
		
		{
			debug(3,"read","entered menu body section.");
			bool found = false;
			std::string menutext;
			while(std::getline(infile, line))
			{
				debug(4,"read","menu body current line = " + line);
				strmanip::removeComment(line);
				RX_fixNewlines(line);
				if(std::regex_search(menutext, RX_itemDef_open)) //ugly af hack. but otherwise it always skips the first non empty line in the first item.
				{
					debug(3,"read","itemdef opened.");
					found = true;
					ParseIntoMenu(menutext);
					break;
				}
				else
				{
					menutext += line;
				}
			}
			if(!found)
			{
				ParseIntoMenu(menutext);
				std::cout << "NOTE: menu \"" + name + "\" in file \"" + filename + "\" seems to contain no items\n";
				return true;
			}
		}
		
		{
			debug(3,"read","entered item section.");
			items = ParseItems(infile,true,1,line);
		}
		
		return true;
	}
	
	const bool menu::writeToFile(const std::string& filename, const std::string indentString, const bool meta)
	{
		std::ofstream outfile(filename,std::ios::trunc);

		if(!outfile.is_open())
		{
			std::cout << "couldnt open outfile \"" << filename << "\"\n";
			std::cout << "possibly the directory doesnt exist\n";
			return false;
		}
		
		
		{
			const std::string newline = "\n"+indentString;
			outfile << "#include \"ui/menudef.h\"\n{\n";
			if(headComment.empty()) 
			{
				std::string uppername(name);
				std::transform(uppername.begin(), uppername.end(), uppername.begin(), ::toupper);
				outfile << indentString << "/* "<<  uppername << newline;
				outfile << "*/\n" << newline;
			}
			else
			{
				outfile << indentString;
				if (headComment.front().find("/*") == std::string::npos) 
					outfile << "/*" << newline;
				for(auto k : headComment)
					outfile << k << newline;
				if (headComment.back().find("*/") == std::string::npos) 
					outfile << "*/" << newline;
			}
			
			if(meta)
			{
				auto t = std::time(nullptr);
				auto tm = *std::localtime(&t);
				outfile << newline << "/*" << newline << "META:";
				outfile << newline << "created using " << AppDescription;
				outfile << newline << "last update: " << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
				outfile << newline << "#items: " << items.size();
				outfile << newline << "*/\n";
			}
			
			outfile << "\n";
			
			if(!assetGlobalDef.empty()) 
			{
				outfile << indentString << "assetGlobalDef {" << newline;
				for(auto k : assetGlobalDef)
					outfile  << indentString << k << newline;
				outfile << "}\n";
			}
			
			outfile << "\n";
			
		}
		{
			const std::string newline = "\n"+indentString+indentString;
			outfile << indentString << "menuDef {" << newline;
			outfile << "name \"" << name << "\"" << newline;
			outfile << "fullscreen " << (fullscreen?"1":"0"+newline+rect.getrectstring()) << newline;
			outfile << "visible " << (visible?"1":"0") << newline;
			if(!type.empty()) { outfile << "type " << type << newline; }
			if(!style.empty()) { outfile << "style " << style << newline; }
			if(!background.empty()) { outfile << "background \"" << background << "\"" << newline; }
			if(border!=0) {outfile << "border " << std::to_string(border) << newline; }
			if(!backcolor.isEmpty) outfile << "backcolor " << backcolor << newline;
			if(!forecolor.isEmpty) outfile << "forecolor " << forecolor << newline;
			if(!focuscolor.isEmpty) outfile << "focuscolor " << focuscolor << newline;
			if(border && !bordercolor.isEmpty) outfile << "bordercolor " << bordercolor << newline;
			if (!onOpen.empty()) 
			{
				const bool ml = onOpen.find("\n")==std::string::npos;
				const std::string mls = (ml?"":newline+indentString);
				outfile << "onOpen { " << mls << onOpen << mls <<" }" << newline; 
			}
			if (!onClose.empty()) 
			{
				const bool ml = onClose.find("\n")==std::string::npos;
				const std::string mls = (ml?"":newline+indentString);
				outfile << "onClose { " << mls << onClose << mls <<" }" << newline; 
			}
			if (!onESC.empty()) 
			{
				const bool ml = onESC.find("\n")==std::string::npos;
				const std::string mls = (ml?"":newline+indentString);
				outfile << "onESC { " << mls << onESC << mls <<" }" << newline; 
			}
		}
		
		{
			for( item k : items )
				outfile << "\n" << k.returndef(indentString,2);
			
			outfile << "\n" << indentString << "}\n}\n";
		}
		
		return true;
	}
	
	void menu::ParseLine(const std::string& s)
	{
		for(const auto& k : RX_MENU_MAP )
		{
			const auto x = RX_ADV_PARSE(s,k.first);
			if(x.first)
			{
				k.second(*this,x.second);
				return;
			}
		}
		debug(5,"parseline","coudlnt parse [[" + s + " ]]");
	}
	
	void menu::ParseIntoMenu(const std::string& s)
	{
		debug(5,"parseintomenu","called with [[ " + s + " ]]");
		for(const auto& k : RX_MENU_MAP )
		{
			const auto x = RX_ADV_PARSE(s,k.first);
			if(x.first)
			{
				k.second(*this,x.second);
			}
		}
	}
	
	void menu::moveItems( const int dx , const int dy )
	{
		for( auto& i : items )
		{
			i.rect.move( dx , dy );
		}
	}
	
	void menu::addItems(const std::list<item>& l)
	{
		items.insert(items.begin(),l.begin(),l.end());
	}
	
	int menu::removeItemsByProperty(std::function<bool(const item&)> lambda)
	{
		int count=0;
		auto it = items.begin();
		while (it != items.end())
		{
			if (lambda(*it))
			{	
				count++;
				it = items.erase(it);
			}
			else
				++it;
		}
		return count;
	}
	
	std::list<item*> menu::getItemsByProperty(std::function<bool(const item&)> lambda)
	{
		std::list<item*> result;
		for( auto& i : items )
		{
			if(lambda(i)) result.push_back(&i);
		}
		return result;
	}
}

// kate: space-indent off; replace-tabs off
