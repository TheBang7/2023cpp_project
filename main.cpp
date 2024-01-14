#include "myMap.h"
#include <iostream>
#include "viewMap.h"
#include<easyx.h>
#include<graphics.h>
#include <conio.h>

#include "mapCtrl.h"
constexpr char key_up = 'W';
constexpr char key_down = 'S';
constexpr char key_left = 'A';
constexpr char key_right = 'D';
constexpr char key_quit = '0';
constexpr char key_restart = 'R';
constexpr char key_pause = VK_ESCAPE;
constexpr char key_back = 'Q';

int main(int argc, char* argv[])
{
	std::cout << "begin" << std::endl;
	MyMap map(8, 8);
	map.loadMap("resource/map/test1.txt");
	map.printMap();
	map.setMapName("test3");
	MyMap* infMap = new MyMap(true);
	ViewMap viewMap(&map);
	MapCtrl ctr(&viewMap, infMap);
	MapCtrl* ctrl = &ctr;
	ctrl->begin();
	bool quit = false;
	bool pause = false;
	while (!quit)
	{
		if (GetAsyncKeyState(key_up) & 0x8001 && !pause)
		{
			std::cout << "Move Up!" << std::endl;
			bool flag = ctrl->dealUp();
			if (flag)
			{
				std::cout << "Game over!" << std::endl;
				quit = true;
			}
			ctrl->getMap()->printMap();
		}
		else if (GetAsyncKeyState(key_down) & 0x8001 && !pause)
		{
			std::cout << "Move Down!" << std::endl;
			bool flag = ctrl->dealDown();
			if (flag)
			{
				std::cout << "Game over!" << std::endl;
				quit = true;
			}
			ctrl->getMap()->printMap();
		}
		else if (GetAsyncKeyState(key_left) & 0x8001 && !pause)
		{
			std::cout << "Move Left!" << std::endl;
			bool flag = ctrl->dealLeft();
			if (flag)
			{
				std::cout << "Game over!" << std::endl;
				quit = true;
			}
			ctrl->getMap()->printMap();
		}
		else if (GetAsyncKeyState(key_right) & 0x8001 && !pause)
		{
			std::cout << "Move Right!" << std::endl;
			bool flag = ctrl->dealRight();
			if (flag)
			{
				std::cout << "Game over!" << std::endl;
				quit = true;
			}
			ctrl->getMap()->printMap();
		}
		else if (GetAsyncKeyState(key_back) & 0x8001 && !pause)
		{
			std::cout << "Back One Step!" << std::endl;
			ctrl->dealBack();
			ctrl->getMap()->printMap();
		}
		else if (GetAsyncKeyState(key_quit) & 0x8001)
		{
			std::cout << "Quit Game!" << std::endl;
			ctrl->dealQuit();
			map.saveMap("resource/map/" + map.getMapName() + ".txt");
			quit = true;
		}
		else if (GetAsyncKeyState(key_restart) & 0x8001)
		{
			std::cout << "Restart Game!" << std::endl;
			map.loadMap("resource/map/test1.txt");
			map.printMap();
			map.setMapName("test3");
			ctrl->setMap(&map);
			ctrl->begin();
			MyMap* infMap = new MyMap(true);
			delete ctr.infMap;
			ctr.infMap = infMap;
		}
		else if (GetAsyncKeyState(key_pause) & 0x8001)
		{
			pause = !pause;
		}

		Sleep(200);
	}
	return 0;
}
