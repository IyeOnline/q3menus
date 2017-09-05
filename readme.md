# q3menus

A c++ libary (and example main files) to quickly edit quake 3 .menu files. Supports various features, including, but not limited to reading and writing to files. Who would have thought.
Technically this project is using C++ as a script language (which is kind of not what its made for, but w/e).
I dont strongly recommend using this in an IDE of some sort.

## Getting started

### Installation
```
#get the repository. maybe you just download it, maybe you use git. maybe you type all the files by yourself. dont care.
mkdir build
cd build
cmake ..
make
./q3menus
#profit
```

### Getting to know the features
Take a look at "src/main.cpp", for a simple program showing the most basic features.
I also included "src/damagemenu.cpp", which is the program that should create my fancy weapon select module with a rotating player model and stuff. (note that when i originally created that menu, the lib wasnt nearly as advanced and i basically just wrote items to files. i am fairly sure that i updated it correctly however. at least it compiles and runs...)

## Documentaion

### namespace
Everything (except for some helper functions) in this project lies in the q3menus:: namespace

### classes
for now, all member variables of all classes are public, to allow for easier manipulation

#### q3menu::item
this class is what you would see as an 'itemDef' in your .menu file. it has pretty much all the properties an itemDef could have.

Notable functions:
* string returndef(indentString,N)
returns a string containing the item. It will be indented N times using indentString
* void init_\*( ... )
There is multiple versions of this, setting members that are somehow connected (e.g. everything related to text)
* list<item> ParseItems(infilestream)
parses an filestream into a list of items. usefull when reading in only items for a file that isnt a complete menu in itself. should work on a single incomplete item as well.

#### q3menu::menu
this is a menu. contains everything, from comments at the top of the file, to the assetsGlobalDef to the menus settings and items

Notable functions:
* readFromFile(filename)
reads the file with the given name into the menu
* writeToFile(filename)
write the menu to a file with the given filename
* int itemCount()
returns the number of items
* moveItems(dx,dy)
moves all items in the menu, by (dx,dy)
* addItems(list<item>)
adds the given items to the menu
* int removeItemsByProperty(lambda)
removes all items that fullfill the boolean lambda 
* list<item*> getItemsByProperty)lambda)
gets a list of pointers to items that match the given boolean lambda

#### q3menu::rectType
your classic "rect". has movement and set features for both Pos and Size members

#### q3menu::color
rgba color, as common in q3menus. has a couple of different constructors and a set method
