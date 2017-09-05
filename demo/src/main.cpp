#include <iostream>
#include <fstream>
#include <list>

#include "q3menus.h"

int main()
{
	using cIr = const q3menus::item&; //const item ref type alias
	
	const std::string indentstring = "\t";
	const std::string ifname = "data/in.menu";
	const std::string ofname = "output/out.menu";

	q3menus::menu testmenu; //create a menu
	
	std::cout << "reading menu from file \"" << ifname << "\"\n";
	if (testmenu.readFromFile(ifname)) //populate that menu by reading in a file, given by its name
	{
		std::cout << "successfully read menu \"" + testmenu.name + "\" with " << testmenu.itemCount() << " items\n"; //lets see how many items we found
	}
	
	{ //example showing  how to mass operate on items with a given property. granted that massTransform actually just is a wraper around std::for_each
		auto itemlist = testmenu.getItemsByProperty([](const q3menus::item& i){return i.name=="UNNAMED";}); //get all items with the name "UNNAMED" (the default name)
		std::cout << itemlist.size() << " unnamed items found\n"; //lets see how many unnamed items we found
		q3menus::massTransform(itemlist,[](q3menus::item* i){i->name = "NOW NAMED";}); //rename all items in the list to "NOT NAMED"
		q3menus::massTransform(itemlist,[](q3menus::item* i){i->rect = q3menus::rectType(1,2,3,4);i->bordercolor = q3menus::color(1,1,0,1);});//set the position and bordercolor of all items in that lhat list
	}
	
	std::cout << std::endl;
	
	{ //example showing how to do something with all items
		std::cout << "items:\n";
		for(const auto& k : testmenu.items)
		{
			std::cout << "\t" << k.name << "\n";
		}
	}
	
	std::cout << std::endl;
	
	{ //example showing how to remove items with a given propery. here, their name should contain the string "option"
		const auto c = testmenu.removeItemsByProperty([](cIr& i){return i.name.find("option")!=std::string::npos;}); //removes all items matching the conidion. note that cIr is a type alias on const q3menus::item&, to save typing
		std::cout << "removed " << c << " items.\n";
		std::cout << testmenu.itemCount() << " items remaining\n";
	}
	
	std::cout << std::endl;
	
	if(testmenu.writeToFile(ofname, indentstring)) //write that menu back to a file, given using the given indentsting
	{
		std::cout << "succesfully wrote menu \"" << testmenu.name << "\" to file \"" << ofname << "\".\n" << std::endl;
	}
	return EXIT_SUCCESS;
}


// kate: space-indent off; replace-tabs off
