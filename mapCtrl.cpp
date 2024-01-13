#include "mapCtrl.h"
#include "MyMap.h"
#include "viewMap.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>


MapCtrl::MapCtrl(ViewMap* viewMap)
{
	this->viewMap = viewMap;
	this->myMap = viewMap->getMap();
	manAreaBefore = Prop::FLOOR;
}

MapCtrl::~MapCtrl()
{
	while (!backStack.empty())
	{
		// 循环弹出栈中的所有元素
		backStack.pop();
	}
}


void MapCtrl::begin()
{
	bool quit = false;
	viewMap->begin();
}

void MapCtrl::dealQuit()
{
}


void MapCtrl::ownMapMove(MyMap* map, int rowChange, int colChange, int count, int initRow, int initCol,
                         MapGrid* firstGrid, bool isInitMap)
{
	MyChange change(count + 1);
	change.all = count + 1;
	for (int i = 0; i <= count; i++)
	{
		change.row[i] = initRow + i * rowChange;
		change.col[i] = initCol + i * colChange;
		change.init[i] = map->getElementType(change.row[i], change.col[i]);
		if (change.init[i] == Prop::SUB_MAP)
		{
			change.initSubMap[i] = map->getSubMap(change.row[i], change.col[i]);
		} //将subMap指针载入数组
		/*
		 *两种情况，如果是当前地图，则change[0]代表人在的位置，如果是别的地图，代表入口或出口位置
		 */
		if (i == 0)
		{
			if (isInitMap)
				change.final[i] = map->getElementRemainsType(initRow, initCol);
			else
			{
				change.final[i] = firstGrid->type;
				if (firstGrid->type == Prop::SUB_MAP)
				{
					change.finalSubMap[i] = firstGrid->map;
				}
			}
		}
		else
		{
			change.final[i] = change.init[i - 1];
			if (change.final[i] == Prop::SUB_MAP)
			{
				change.finalSubMap[i] = map->getSubMap(change.row[i - 1], change.col[i - 1]);
			}
			else if ((change.init[i] == Prop::HIT || change.init[i] == Prop::BOX_DEST) && change.final[i] ==
				Prop::BOX)
			{
				change.final[i] = Prop::HIT;
			}
			else if ((change.init[i] == Prop::FLOOR) && change.final[i] == Prop::HIT)
			{
				change.final[i] = Prop::BOX;
			}
		}
	}
	map->dealChange(&change);
	if (viewMap->getMap() == map)
		viewMap->dealChange(&change);
	backStack.push(&change);
}

void MapCtrl::transMapMove(MyMap* map, int const rowChange, int const colChange, int initRow, int initCol,
                           MapGrid* firstGrid, bool dealingInitMap)
{
	int count = 0;
	int finalRow = initRow;
	int finalCol = initCol;
	while (map->isInMap(finalRow, finalCol) &&
		(map->getElementType(finalRow, finalCol) == Prop::BOX ||
			map->getElementType(finalRow, finalCol) == Prop::MAN ||
			map->getElementType(finalRow, finalCol) == Prop::HIT ||
			map->getElementType(finalRow, finalCol) == Prop::SUB_MAP))
	{
		count++;
		finalCol += colChange;
		finalRow += rowChange;
	}
	if (!map->isInMap(finalRow, finalCol) || map->getElementType(finalRow, finalCol) == Prop::WALL)
	{
		int backRow = finalRow;
		int backCol = finalCol;
		int tcount = count;
		for (int i = 1; i <= count; i++)
		{
			if (map->getElementType(backRow, backCol) == Prop::SUB_MAP)
			{
				MyMap* subMap = map->getSubMap(backRow, backCol);
				if (subMap->getEntranceByMoveDirection(rowChange, colChange))
				{
					myPosition position = subMap->getEntrancePositionByMoveDirection(rowChange, colChange);
					if (subMap->canMove(rowChange, colChange, position.row, position.col))
					{
						transMapMove(subMap, rowChange, colChange, position.row, position.col,
						             map->getElement(backRow - rowChange, backCol - colChange), false);
						if (map->getElementType(backRow - rowChange, backCol - colChange) == Prop::MAN)
						{
							std::cout << "2345" << std::endl;
							setMap(subMap);
						}

						ownMapMove(map, rowChange, colChange, tcount - 1, initRow, initCol, firstGrid, dealingInitMap);
					}
					break;
				}
			}
			backCol -= colChange;
			backRow -= rowChange;
			tcount--;
		}
		dealingInitMap = true;
	}
	else
	{
		ownMapMove(map, rowChange, colChange, count, initRow, initCol, firstGrid, dealingInitMap);
	}
}

void MapCtrl::dealMove(int const rowChange, int const colChange)
{
	int manRow = this->myMap->getManPositionRow();
	int manCol = this->myMap->getManPositionCol();
	transMapMove(this->myMap, rowChange, colChange, manRow, manCol,
	             myMap->getElement(manRow, manCol), true);
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

void MapCtrl::setMap(MyMap* map)
{
	this->myMap = map;
	viewMap->setMap(map);
	viewMap->begin();
}
