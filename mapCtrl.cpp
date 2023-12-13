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
	this->myMap = viewMap->getMap();
	manAreaBefore = Prop::FLOOR;
}

void MapCtrl::begin()
{
	bool quit = false;
	viewMap->begin();

	while (!quit)
	{
		if (GetAsyncKeyState(key_up) & 0x8001)
		{
			std::cout << "Move Up!" << std::endl;
			dealUp();
		}
		else if (GetAsyncKeyState(key_quit) & 0x8001)
		{
			std::cout << "Quit Game!" << std::endl;
			this->dealQuit();
			quit = true;
		}
		else if (GetAsyncKeyState(key_down) & 0x8001)
		{
			std::cout << "Move Down!" << std::endl;
			this->dealDown();
		}
		else if (GetAsyncKeyState(key_left) & 0x8001)
		{
			std::cout << "Move Left!" << std::endl;
			this->dealLeft();
		}
		else if (GetAsyncKeyState(key_right) & 0x8001)
		{
			std::cout << "Move Right!" << std::endl;
			this->dealRight();
		}

		Sleep(200);
	}
}

void MapCtrl::dealQuit()
{
}

void MapCtrl::dealMove(int const rowChange, int const colChange)
{
	int manRow = this->myMap->getManPositionRow();
	int manCol = this->myMap->getManPositionCol();

	int count = 1;
	int finalRow = manRow + rowChange;
	int finalCol = manCol + colChange;
	while (myMap->isInMap(finalRow, finalCol) &&
		(myMap->getElement(finalRow, finalCol) == Prop::BOX || myMap->getElement(finalRow, finalCol) == Prop::HIT))
	{
		count++;
		finalCol += colChange;
		finalRow += rowChange;
	}
	if (!myMap->isInMap(finalRow, finalCol) || myMap->getElement(finalRow, finalCol) == Prop::WALL)return;
	else
	{
		MyChange change(count + 1);
		change.all = count + 1;
		for (int i = 0; i <= count; i++)
		{
			change.row[i] = manRow + i * rowChange;
			change.col[i] = manCol + i * colChange;
			change.init[i] = myMap->getElement(change.row[i], change.col[i]);
			if (i == 0)
			{
				change.final[i] = manAreaBefore;
			}
			else if (i == 1)
			{
				change.final[i] = Prop::MAN;
				manAreaBefore = change.init[i] == Prop::HIT || change.init[i] == Prop::BOX_DEST
					                ? Prop::BOX_DEST
					                : Prop::FLOOR;
			}
			else
			{
				change.final[i] = change.init[i - 1];
				if ((change.init[i] == Prop::HIT || change.init[i] == Prop::BOX_DEST) && change.final[i] == Prop::BOX)
				{
					change.final[i] = Prop::HIT;
				}
				else if ((change.init[i] == Prop::FLOOR) && change.final[i] == Prop::HIT)
				{
					change.final[i] = Prop::BOX;
				}
			}
		}


		myMap->dealChange(&change);
		viewMap->dealChange(&change);
		backStack.push(change);
	}
}

void MapCtrl::dealUp()
{
	dealMove(-1, 0);
}


void MapCtrl::dealDown()
{
	dealMove(1, 0);
}

void MapCtrl::dealLeft()
{
	dealMove(0, -1);
}

void MapCtrl::dealRight()
{
	dealMove(0, 1);
}
