#include "mapCtrl.h"
#include "MyMap.h"
#include "viewMap.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>


MapCtrl::MapCtrl(ViewMap* viewMap)
{
	this->viewMap = viewMap;
	viewMap->setCtrl(this);
}

void MapCtrl::begin()
{
	bool quit = false;
	viewMap->begin();

	while (!quit)
	{
		if (GetAsyncKeyState('W') & 0x8001)
		{
			std::cout << "Move Up!" << std::endl;
			dealUp();
		}
		else if (GetAsyncKeyState('Q') & 0x8001)
		{
			std::cout << "Quit Game!" << std::endl;
			dealQuit();
			quit = true;
		}
		else if (GetAsyncKeyState('S') & 0x8001)
		{
			std::cout << "Move Down!" << std::endl;
			dealDown();
		}
		else if (GetAsyncKeyState('A') & 0x8001)
		{
			std::cout << "Move Left!" << std::endl;
			dealLeft();
		}
		else if (GetAsyncKeyState('D') & 0x8001)
		{
			std::cout << "Move Right!" << std::endl;
			dealRight();
		}

		Sleep(200);
	}
}

void MapCtrl::dealQuit()
{
}

void MapCtrl::dealUp()
{
}

void MapCtrl::dealDown()
{
}

void MapCtrl::dealLeft()
{
}

void MapCtrl::dealRight()
{
}
