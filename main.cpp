#include "myMap.h"
#include <iostream>
#include "viewMap.h"
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include "viewmenu.h"
#include "mapCtrl.h"
#include <sstream>


int main(int argc, char* argv[])
{
	int cen;
	int room;
	int ifload;
	initgraph(1250, 1000);
	menu1(cen,room);
	std::cout << "begin" << std::endl;
	while (true) {
		MyMap map(8, 8);
		std::string filename;
		std::stringstream ss;
		ss << "resource/map/" << cen << "." << room << ".txt";
		filename = ss.str();
		map.loadMap(filename);
		map.printMap();
		map.setMapName("1.1");
		ifload = 0;
		MyMap* infMap = new MyMap(true);
		ViewMap viewMap(&map);
		MapCtrl ctr(&viewMap, infMap);
		MapCtrl* ctrl = &ctr;
		ctrl->begin(cen,room,ifload);
		diyiceng(cen,cen, room);
	}
	

	return 0;
}
