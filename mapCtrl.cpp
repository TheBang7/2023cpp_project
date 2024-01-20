#include "mapCtrl.h"
#include "MyMap.h"
#include "viewMap.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <sstream>
#include "viewmenu.h"


MapCtrl::MapCtrl(ViewMap* viewMap, MyMap* infMap)
{
	this->viewMap = viewMap;
	this->myMap = viewMap->getMap();
	this->mainMap = viewMap->getMap();
	this->initMap = viewMap->getMap();
	manAreaBefore = Prop::FLOOR;
	this->infMap = infMap;
}

MapCtrl::~MapCtrl()
{
	while (!backStack.empty())
	{
		// 循环弹出栈中的所有元素
		backStack.pop();
		backIdStack.pop();
		backMapStack.pop();
	}
}


void MapCtrl::begin(int& cen,int&room,int& ifload)
{
	viewMap->begin();
	bool quit = false;
	bool pause = false;
	MapCtrl* ctrl = this;
	MyMap* map = this->myMap;

	// 添加菜单按钮
	int x = 50, y = 100; // 将 y 坐标上移
	int w = 100, h = 60; // 增大按钮的宽度和高度
	TCHAR text[20] = "save";
	drawButton(x, y, w, h, text, WHITE);
	y += 70; // 更新 y 坐标
	TCHAR textMenu[20] = "load";
	drawButton(x, y, w, h, textMenu, WHITE);

	
	while (!quit)
	{

		if (GetAsyncKeyState(0x49) & 0x8000)
		{
			choosesave(mainMap, cen, room);
			break;
		}

		if (GetAsyncKeyState(0x4F) & 0x8000)
		{
			// 'o' 键被按下
			chooseload(mainMap, cen, room);
			ifload = 1;
			break;
		}




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
			diyiceng(cen, cen, room);
			map->saveMap("resource/map/" + map->getMapName() + ".txt");
			quit = true;
		}
		else if (GetAsyncKeyState(key_restart) & 0x8001)
		{
			std::cout << "Restart Game!" << std::endl;
			std::stringstream ss;
			ss << "resource/map/" << cen << "." << room << ".txt";
			std::string filename = ss.str();
			map->loadMap(filename);
			map->printMap();
			map->setMapName("test3");
			//ctrl->setMap(map);
			ctrl->begin(cen,room,ifload);
			MyMap* infMap = new MyMap(true);
			delete ctrl->infMap;
			ctrl->infMap = infMap;
		}
		else if (GetAsyncKeyState(key_pause) & 0x8001)
		{
			pause = !pause;
		}

		Sleep(100);
	}
}

void MapCtrl::dealQuit()
{

}


void MapCtrl::ownMapMove(MyMap* map, int rowChange, int colChange, int count, int initRow, int initCol,
                         MapGrid* firstGrid, bool isInitMap)
{
	MyChange* change = new MyChange(count + 1);
	change->all = count + 1;
	change->initView = viewMap->getMap();
	change->finalView = viewMap->getMap();
	for (int i = 0; i <= count; i++)
	{
		change->row[i] = initRow + i * rowChange;
		change->col[i] = initCol + i * colChange;
		change->init[i] = map->getElementType(change->row[i], change->col[i]);
		if (change->init[i] == Prop::SUB_MAP)
		{
			change->initFather[i] = map;
			change->initSubMap[i] = map->getSubMap(change->row[i], change->col[i]);
		} //将subMap指针载入数组
		/*
		 *两种情况，如果是当前地图，则change[0]代表人在的位置，如果是别的地图，代表入口或出口位置
		 */
		if (i == 0)
		{
			if (isInitMap)
				change->final[i] = map->getElementRemainsType(initRow, initCol);
			else
			{
				change->final[i] = firstGrid->type;
				if (firstGrid->type == Prop::SUB_MAP)
				{
					change->finalSubMap[i] = firstGrid->map;
					change->finalFather[i] = map;
					/*
					firstGrid->map->outsideMap = map;
					firstGrid->map->outsidePosition.row = change->row[0];
					firstGrid->map->outsidePosition.col = change->col[0];
					*/
				}
				else if (firstGrid->type == Prop::MAN || firstGrid->type == Prop::MAN_HIT)
				{
					change->initView = viewMap->getMap();
					setMap(map);
					change->finalView = viewMap->getMap();
				}
			}
		}
		else
		{
			change->final[i] = change->init[i - 1];
			if (change->final[i] == Prop::SUB_MAP)
			{

				change->finalFather[i] = map->getSubMap(change->row[i - 1], change->col[i - 1])->outsideMap;
				change->finalSubMap[i] = map->getSubMap(change->row[i - 1], change->col[i - 1]);
			}
			else if ((change->init[i] == Prop::HIT || change->init[i] == Prop::BOX_DEST) && change->final[i] ==
				Prop::BOX)
			{
				change->final[i] = Prop::HIT;
			}
			else if ((change->init[i] == Prop::MAN_HIT || change->init[i] == Prop::MAN_DEST) && change->final[i] ==
				Prop::MAN)
			{
				change->final[i] = Prop::MAN_HIT;
			}
			else if (change->init[i] == Prop::FLOOR && change->final[i] == Prop::HIT)
			{
				change->final[i] = Prop::BOX;
			}
			else if ((change->init[i] == Prop::FLOOR || change->init[i] == Prop::BOX_DEST) && change->final[i] ==
				Prop::MAN_HIT)
			{
				change->final[i] = Prop::MAN;
			}
		}
	}
	map->dealChange(change);
	if (viewMap->getMap() == map)
		viewMap->dealChange(change);
	backStack.push(change);
	backIdStack.push(countStep);
	backMapStack.push(map);
}

void MapCtrl::transMapMove(MyMap* map, int const rowChange, int const colChange, int initRow, int initCol,
                           MapGrid* firstGrid, bool dealingInitMap, bool loopTrans)
{
	countInf++;
	int count = 0;
	int finalRow = initRow;
	int finalCol = initCol;
	while (map->isInMap(finalRow, finalCol) &&
		(map->getElementType(finalRow, finalCol) == Prop::BOX ||
			(map->getElementType(finalRow, finalCol) == Prop::MAN && !loopTrans) ||
			(map->getElementType(finalRow, finalCol) == Prop::MAN_HIT && !loopTrans) ||
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
		if (!map->isInMap(finalRow, finalCol))
		{
			backCol -= colChange;
			backRow -= rowChange;
			tcount--;
			if (map->getEntranceByMoveDirection_out(rowChange, colChange) && map != infMap)
			{
				MyMap* out;

				out = map->outsideMap;

				myPosition position;

				position = map->outsidePosition;
				if (out->canMove(rowChange, colChange, position.row + rowChange, position.col + colChange,
				                 false, 0).shouldInf)
				{
					out = infMap;
					position = out->getEntrancePositionByMoveDirection_in(rowChange, colChange);
				}

				if (out->canMove(rowChange, colChange, position.row + rowChange, position.col + colChange,
				                 false, 0).canMove)
				{
					bool loop = out->loopMove(rowChange, colChange, position.row + rowChange,
					                          position.col + colChange, false, 0);
					if (loop)
					{
						MapGrid grid, grid2;
						grid.map = firstGrid->map;
						grid.type = firstGrid->type;
						grid2.map = map->getElement(backRow, backCol)->map;
						grid2.type = map->getElement(backRow, backCol)->type;


						if (!map->isInMap(initRow, initCol))
							ownMapMove(map, rowChange, colChange, tcount, backRow, backCol, &grid, dealingInitMap);
						else
							ownMapMove(map, rowChange, colChange, tcount, initRow, initCol, &grid, dealingInitMap);
						transMapMove(out, rowChange, colChange, position.row + rowChange,
						             position.col + colChange,
						             &grid2, false, loop);
						if (dealingInitMap)
							viewMap->begin();
					}
					else
					{
						MapGrid grid;
						grid.map = map->getElement(backRow, backCol)->map;
						grid.type = map->getElement(backRow, backCol)->type;
						transMapMove(out, rowChange, colChange, position.row + rowChange,
						             position.col + colChange,
						             &grid, false, loop);
						if (grid.type == Prop::MAN || grid.type == Prop::MAN_HIT)
						{
							setMap(out);
						}

						if (!map->isInMap(initRow, initCol))
							ownMapMove(map, rowChange, colChange, tcount + 1, backRow, backCol, firstGrid,
							           dealingInitMap);
						else
							ownMapMove(map, rowChange, colChange, tcount, initRow, initCol, firstGrid, dealingInitMap);
						if (dealingInitMap)
							viewMap->begin();
					}
				}
			}
		}
		else
		{
			for (int i = 1; i <= count; i++)
			{
				backCol -= colChange;
				backRow -= rowChange;
				tcount--;
				if (map->getElementType(backRow, backCol) == Prop::SUB_MAP)
				{
					MyMap* subMap = map->getSubMap(backRow, backCol);
					if (subMap->getEntranceByMoveDirection_in(rowChange, colChange))
					{
						myPosition position = subMap->getEntrancePositionByMoveDirection_in(rowChange, colChange);
						if (subMap->canMove(rowChange, colChange, position.row, position.col, false, 0).canMove)
						{
							subMap->outsidePosition.row = backRow;
							subMap->outsidePosition.col = backCol;
							bool loop = subMap->loopMove(rowChange, colChange, position.row, position.col, false, 0);
							if (loop)
							{
								MapGrid grid;
								MapGrid grid2;
								grid.map = firstGrid->map;
								grid.type = firstGrid->type;
								grid2.map = map->getElement(backRow - rowChange, backCol - colChange)->map;
								grid2.type = map->getElement(backRow - rowChange, backCol - colChange)->type;
								ownMapMove(map, rowChange, colChange, tcount - 1, initRow, initCol, &grid,
								           dealingInitMap);

								transMapMove(subMap, rowChange, colChange, position.row, position.col,
								             &grid2, false, loop);
								if (grid2.type == Prop::MAN || grid2.type == Prop::MAN_HIT)
								{
									setMap(subMap);
								}
								if (dealingInitMap)
									viewMap->begin();
							}
							else
							{
								MapGrid grid, grid2;
								grid2.map = map->getElement(backRow - rowChange, backCol - colChange)->map;
								grid2.type = map->getElement(backRow - rowChange, backCol - colChange)->type;
								transMapMove(subMap, rowChange, colChange, position.row, position.col,
								             &grid2, false, loop);
								if (grid2.type == Prop::MAN || grid.type == Prop::MAN_HIT)
								{
									setMap(subMap);
								}

								ownMapMove(map, rowChange, colChange, tcount - 1, initRow, initCol, firstGrid,
								           dealingInitMap);
								if (dealingInitMap)
									viewMap->begin();
							}
						}
						break;
					}
				}
			}
			dealingInitMap = true;
		}
	}
	else
	{
		ownMapMove(map, rowChange, colChange, count, initRow, initCol, firstGrid, dealingInitMap);
	}
}

bool MapCtrl::dealMove(int const rowChange, int const colChange)
{
	countStep++;
	int manRow = this->myMap->getManPositionRow();
	int manCol = this->myMap->getManPositionCol();
	transMapMove(this->myMap, rowChange, colChange, manRow, manCol,
	             myMap->getElement(manRow, manCol), true, false);
	countInf = 0;
	if (initMap->shouldCheck)
	{
		std::cout << "check!" << std::endl;
		initMap->shouldCheck = false;
		return initMap->checkMap();
	}
}

bool MapCtrl::dealUp()
{
	return dealMove(-1, 0);
}


bool MapCtrl::dealDown()
{
	return dealMove(1, 0);
}

bool MapCtrl::dealLeft()
{
	return dealMove(0, -1);
}

bool MapCtrl::dealRight()
{
	return dealMove(0, 1);
}

void MapCtrl::dealBack()
{
	if (backIdStack.empty())return;
	const int id = backIdStack.top();
	int count = 0;
	MyMap* finalView = backStack.top()->initView;
	while (!backIdStack.empty() && backIdStack.top() == id)
	{
		count++;
		backIdStack.pop();
		backMapStack.top()->backChange(backStack.top());
		if (viewMap->getMap() == backMapStack.top())
			viewMap->backChange(backStack.top());
		if (backStack.top()->initView != nullptr)
			finalView = backStack.top()->initView;
		backMapStack.pop();
		MyChange* change = backStack.top();
		backStack.pop();
		if (backIdStack.empty() || backIdStack.top() != id)
		{
			if (viewMap->getMap() != finalView)
			{
				myMap = finalView;
				setMap(finalView);
				viewMap->begin();
			}
		}
		delete change;
	}
}

void MapCtrl::setMap(MyMap* map)
{
	this->myMap = map;
	viewMap->setMap(map);
}

MyMap* MapCtrl::getMap()
{
	return myMap;
}
