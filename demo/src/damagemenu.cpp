#include <iostream>
#include "item.h"
#include "menu.h"

	
void damagemenu()
{
	//file stuff
	std::string outfilename;
	std::string infilename;
	const std::string indatapath = "../data/";
	const std::string outdatapath = "../output/ui/";
	const std::string prefix = "\t\t";
	std::ofstream outfile;
	std::ifstream infile;

	//indata entires marking guns in indata
	const std::vector<int> primaryIDs = { 4 , 5 , 6 , 7 , 8 , 9 , 10 , 13 , 14 , 15 , 16 , 19 , 20 , 21 , 22 };
	const std::vector<int> secondaryIDs = { 4 , 5 , 6 , 19 , 21 , 22 };
	const std::vector<int> sidearmIDs = { 2 , 3 , 17 , 18 , 23 };
	const std::vector<std::vector<int>> IDs = { primaryIDs , secondaryIDs , sidearmIDs };
	const std::vector<std::string> menunames = { "primary" , "secondary" , "sidearm" };

	//defining positions
	//textinfo: rect 366  273  192  76	
	const q3menus::rectType headrect( 406 , 40 , 20 , 20 );
	const q3menus::rectType torsorect( 409 , 80 , 20 , 20 );
	const q3menus::rectType armsrect( 461 , 95 , 20 , 20 );
	const q3menus::rectType groinrect( 414 , 115 , 20 , 20 );
	const q3menus::rectType upperrect( 450 , 135 , 20 , 20 );
	const q3menus::rectType lowerrect( 396 , 160 , 20 , 20 );
	const q3menus::rectType footrect( 458 , 178 , 20 , 20 );
	const q3menus::rectType boxrect( 366 , 107 , 192 , 168 );
	//DETAIL text:
	const q3menus::rectType detailrect( 366 , 349 , 90 , 25 );
	//all hitzone positions
	const std::vector<q3menus::rectType> rectvec = { headrect , torsorect , armsrect , groinrect , upperrect , lowerrect , footrect };



	//const std::vector<rect> zonesvector = {headrect};
	
	const int weapons = 24;
	const int entries = 9;//starting value for entries#
	std::string data[weapons][entries]; //we will merge head+helmet torso+vets groind+butt

	
	
	std::cout << "hi" << std::endl;//say hi
	std::cout << "indatapath is : \t" << indatapath << std::endl;
	std::cout << "outdatapath is :\t" << outdatapath << std::endl;
	
	{
		std::cout << "\nconsidering as primaries: \t";
		for(int i : primaryIDs) std::cout << data[i][1] << " " ; 
		std::cout << "\nconsidering as secondaries: \t";
		for(int i : secondaryIDs) std::cout << data[i][1] << " " ; 
		std::cout << "\nconsidering as sidearms: \t";
		for(int i : sidearmIDs) std::cout << data[i][1] << " " ; 
		std::cout << "\n\n";
	}
	
	{
		std::string indata[weapons][entries+3];
		infilename = "dmg43.txt";
		
		std::cout << "reading " << infilename << "...";// << "check out my indata:" << std::endl; 
		infile.open(indatapath+infilename);
	
		std::string line;
		{
			int i=0;
			while (std::getline(infile, line))
			{
				std::istringstream iss(line);
					
				if (!(iss >> indata[i][0] >> indata[i][1] >> indata[i][2] >> indata[i][3] >> indata[i][4] >> indata[i][5] >> indata[i][6] >> indata[i][7] >> indata[i][8] >> indata[i][9] >> indata[i][10] >> indata[i][11] )) 
				{ 
					break; 
				} // error
				for(int a = 0;a<entries+3;a++)
				{
// 					std::cout << indata[i][a] << "\t";
				}
// 				std::cout << std::endl;
				i++;
			}
		}
		infile.close();
		std::cout << " done\n\n";
	
		std::cout << "check out my refined data:\n";
		for(int i=0;i<weapons;i++)
		{
			if(i!=0) //color the damages
			{ 
				std::string colorme;
				for(int k=2;k<entries+3;k++)
				{
					{
						if(std::stoi( indata[i][k] ) == 100 ) // == 100
						{ colorme = "^2";}
						else if(std::stoi( indata[i][k] ) >= 75 ) //in ( 75 - 100 )
						{ colorme = "";}
						else if(std::stoi( indata[i][k] ) >= 50 ) //in ( 50 - 74 )
						{ colorme = "^8";}
						else if(std::stoi( indata[i][k] ) >= 25 ) //in ( 25 - 49 )
						{ colorme = "^3";}
						else									//in ( -inf - 24 )	
						{ colorme = "^1";} 
					}
					indata[i][k] = colorme + indata[i][k];
				}
			}
			data[i][0] = indata[i][0];
			data[i][1] = indata[i][1];
			data[i][2] = indata[i][2] + " ^7/ " + indata[i][3];
			data[i][3] = indata[i][4] + " ^7/ " + indata[i][5];
			data[i][4] = indata[i][6];
			data[i][5] = indata[i][7] + " ^7/ " + indata[i][8];
			data[i][6] = indata[i][9];
			data[i][7] = indata[i][10];
			data[i][8] = indata[i][11];
			
			for(int k = 0 ; k < entries ; k++ )
			{
				std::cout << data[i][k] << "\t\t";
			}
			std::cout << "\n";
		}
	}
	
	for(int i=0;i<3;++i) //MENU LOOP
	{
		std::cout << std::endl;
		outfilename = outdatapath + "ingame_select_gear_" + menunames[i] + ".menu";
		
		infilename = indatapath + menunames[i] + "_header.txt";
		
		
		q3menus::menu testmenu;
		testmenu.readFromFile(infilename);
		std::cout << "read menu \"" << testmenu.name << "\" with " << testmenu.itemCount() << " items from \"" << infilename << "\"\n";
		
		{
			infilename = indatapath + "playermodels.txt";
			infile.open(infilename);
			const auto newitems = q3menus::ParseItems(infile);
			std::cout << "read " << newitems.size() << " items from \"" << infilename << "\"\n";
			testmenu.addItems(newitems);
			std::cout << "added those to the menu\n";
		}

		{
			q3menus::item box;
			// add DETAIL text
			std::cout << "adding detail text item\n";
			box.headcomment ="DETAIL BOX";
			box.background = "";
			box.init_general( "detail_text" , "info", detailrect , "1" );
			box.init_style( "WINDOW_STYLE_FILLED" , 1 , q3menus::color(.2,.2,.2,.3) , q3menus::color(1,1,1,1.), q3menus::color(.5,.5,.5,.7), q3menus::color(), true , true );
			box.init_text( "DETAILS" , "0" , 5 , 18 , .3 );
			
			testmenu.items.push_back(box);
		}
		
		{ // do hit zones
			std::cout << "creating hitzone items\n";
			
			q3menus::item citem;
			citem.wrapped = true;
			citem.init_style( "WINDOW_STYLE_FILLED" , 0 , q3menus::color(0,0,0,0) , q3menus::color(1,1,1,1.), q3menus::color(0,0,0,1.), q3menus::color(), false , true );
			
			for(int wc : IDs[i] ) // weapons loop
			{
				citem.headcomment= data[wc][1] + " DAMAGES";
				for(int hz = 2; hz < entries ; hz ++) //hitzones loop	
				{
					const std::string textstring = data[0][hz] + "\\r\"\n" + prefix + "\t\"" + data[wc][hz];
					//std::cout << "\t\t" << data[0][hz] << std::endl;
					citem.init_general( data[wc][1] +  "_info" , "info", rectvec[hz-2] , "1" );
					citem.init_text( textstring , "0" , 35 , 85 , .15 );
					testmenu.items.push_back(citem);
				}
			}
		}

		std::cout << "writing menu \"" << testmenu.name << "\" with " << testmenu.itemCount() << " items to  file \"" << outfilename << "\"\n";
		testmenu.writeToFile(outfilename);
		infile.close();
	}
	std::cout << "\n DONE." << std::endl;
}
