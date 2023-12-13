#include "myMap.h"
#include <iostream>
#include "viewMap.h"
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
constexpr char key_up = 'W';
constexpr char key_down = 'S';
constexpr char key_left = 'A';
constexpr char key_right = 'D';
constexpr char key_quit = VK_ESCAPE;

int main(int argc, char* argv[])
{
	std::cout << "begin" << std::endl;
	MyMap map(10, 12);
	map.printMap();
	ViewMap viewMap(&map);
	MapCtrl ctr(&viewMap);
	MapCtrl* ctrl = &ctr;
	ctrl->begin();
	bool quit = false;
	while (!quit)
	{
		if (GetAsyncKeyState(key_up) & 0x8001)
		{
			std::cout << "Move Up!" << std::endl;
			ctrl->dealUp();
		}
		else if (GetAsyncKeyState(key_quit) & 0x8001)
		{
			std::cout << "Quit Game!" << std::endl;
			ctrl->dealQuit();
			quit = true;
		}
		else if (GetAsyncKeyState(key_down) & 0x8001)
		{
			std::cout << "Move Down!" << std::endl;
			ctrl->dealDown();
		}
		else if (GetAsyncKeyState(key_left) & 0x8001)
		{
			std::cout << "Move Left!" << std::endl;
			ctrl->dealLeft();
		}
		else if (GetAsyncKeyState(key_right) & 0x8001)
		{
			std::cout << "Move Right!" << std::endl;
			ctrl->dealRight();
		}

		Sleep(200);
	}
	return 0;
}
