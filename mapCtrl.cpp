#include "mapCtrl.h"
#include "MyMap.h"
#include "viewMap.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <sstream>

#include "myAi.h"
#include "viewmenu.h"


MapCtrl::MapCtrl(ViewMap* viewMap, MyMap* infMap)
{
	this->viewMap = viewMap;
	this->myMap = viewMap->getMap();
	this->mainMap = viewMap->getMap();
	this->initMap = viewMap->getMap();
	manAreaBefore = Prop::FLOOR;
	viewLastRound = myMap;
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

bool loadAndRstView(ViewMap* viewMap, MyMap* map)
{
	map->printed = true;
	int row = map->getNumRows();
	int col = map->getNumCols();
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (map->getElementType(i, j) == Prop::MAN_HIT || map->getElementType(i, j) == Prop::MAN)
			{
				viewMap->setMap(map);
				return true;
			}
		}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if ((map->getElementType(i, j) == Prop::SUB_MAP || map->getElementType(i, j) == Prop::MAIN_SUB) && !map->
				getSubMap(i, j)->printed)
			{
				if(loadAndRstView(viewMap, map->getSubMap(i, j)))return true;
			}
		}
	return false;

}


void MapCtrl::begin(int& cen, int& room, int& ifload)
{
	viewMap->setMap(this->myMap);
	if (!isTraining)
		viewMap->begin();
	bool quit = false;
	bool pause = false;
	MapCtrl* ctrl = this;
	MyMap* map = this->myMap;

	while (!quit)
	{
		viewLastRound = viewMap->getMap();

		if (GetAsyncKeyState('I') & 0x8001)
		{
			cleardevice();
			choosesave(initMap, cen, room);
			if (!isTraining)
				viewMap->begin();
		}
		else if (GetAsyncKeyState('O') & 0x8001)
		{
			cleardevice();
			chooseload(initMap, cen, room);
			cleardevice();
			if(!loadAndRstView(viewMap, initMap))viewMap->setMap(infMap);
			setMap(viewMap->getMap());
			for (MyMap* map : initMap->mapList)
			{
				map->printed = false;
			}
			initMap->printed = false;
			if (!isTraining)
				viewMap->begin();
		}
		else if (GetAsyncKeyState(key_up) & 0x8001 && !pause)
		{
			std::cout << "Move Up!" << std::endl;
			bool flag = ctrl->dealUp();
			ctrl->getMap()->printMap();
			if (flag)
			{
				std::cout << "Game over!" << std::endl;
				quit = true;
			}
		}
		else if (GetAsyncKeyState(key_down) & 0x8001 && !pause)
		{
			std::cout << "Move Down!" << std::endl;
			bool flag = ctrl->dealDown();
			ctrl->getMap()->printMap();
			if (flag)
			{
				std::cout << "Game over!" << std::endl;
				quit = true;
			}
		}
		else if (GetAsyncKeyState(key_left) & 0x8001 && !pause)
		{
			std::cout << "Move Left!" << std::endl;
			bool flag = ctrl->dealLeft();
			ctrl->getMap()->printMap();
			if (flag)
			{
				std::cout << "Game over!" << std::endl;
				quit = true;
			}
		}
		else if (GetAsyncKeyState(key_right) & 0x8001 && !pause)
		{
			std::cout << "Move Right!" << std::endl;
			bool flag = ctrl->dealRight();
			ctrl->getMap()->printMap();
			if (flag)
			{
				std::cout << "Game over!" << std::endl;
				quit = true;
			}
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
			//map->saveMap("resource/map/" + map->getMapName() + ".txt");
			break;
		}
		else if (GetAsyncKeyState(key_restart) & 0x8001)
		{
			std::cout << "Restart Game!" << std::endl;
			ctrl->dealRestart(cen, room);
			//ctrl->begin(cen, room, ifload);
		}
		else if (GetAsyncKeyState(key_pause) & 0x8001)
		{
			pause = !pause;
			if (pause)
				std::cout << "Pause Game!" << std::endl;
			else
				std::cout << "Continue Game!" << std::endl;
		}
		else if (GetAsyncKeyState('9') & 0x8001)
		{
			std::cout << "Start Ai!" << std::endl;
			dealAi(cen, room);
		}

		Sleep(200);
	}
	if (quit == 1)
	{
		celebrate();
	}
}

void MapCtrl::dealAi(int cen, int room)
{
	MyAi ai;
	int TrainTime = 500000;
	int maxStep = 100;
	isTraining = true;
	double grade_sum = 0;
	bool success = false;
	for (int i = 0; i < TrainTime; i++)
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
		{
			break;
		}
		if (i % 1000 == 0)
		{
			std::cout << "Train times: " << i << " grade_sum: " << grade_sum << "  success?: ";
			if (success)std::cout << "yes" << std::endl;
			else std::cout << "no" << std::endl;
		}
		grade_sum = 0;
		std::string state, prev_state;
		int state_index = 0, prev_state_index = 0;
		int action = -1, prev_action = -1;
		for (int j = 0; j < maxStep; j++)
		{
			//Sleep(500);
			state = ai.stateAbstration(this->myMap);
			state_index = ai.getStateIndex(state);
			if (j > 0)
			{
				double r = ai.getReward(myMap, prev_state, state, myMap == initMap);
				grade_sum += ai.updateQ_table(state_index, prev_state_index, prev_action, r);
			}
			int t_action = ai.selectAction(state_index, isTraining, action);
			action = t_action;
			bool flag = false;
			switch (action)
			{
			case 0:
				flag = dealUp();
				break;
			case 1:
				flag = dealDown();
				break;
			case 2:
				flag = dealLeft();
				break;
			case 3:
				flag = dealRight();
				break;
			default:
				dealRestart(cen, room);
			}
			prev_state = state;
			prev_state_index = state_index;
			prev_action = action;
			if (flag)
			{
				success = true;
				break;
			}
		}
		double r = ai.getReward(myMap, prev_state, state, myMap == initMap);
		grade_sum += ai.updateQ_table(state_index, prev_state_index, prev_action, r);
		dealRestart(cen, room);
	}
	isTraining = false;
	std::cout << "Train Finish";
	dealRestart(cen, room);
	bool flag = false, ff = false;
	success = false;
	Sleep(500);
	while (!flag && !ff)
	{
		std::string state, prev_state;
		int state_index = 0, prev_state_index = 0;
		int action = -1, prev_action = -1;
		for (int j = 0; j < maxStep; j++)
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
			{
				ff = true;
				break;
			}
			Sleep(300);
			state = ai.stateAbstration(this->myMap);
			state_index = ai.getStateIndex(state);
			std::vector<double> value = ai.q_table[state_index];
			int t_action = ai.selectAction(state_index, isTraining, action);
			action = t_action;
			if (j > 0)
			{
				double r = ai.getReward(myMap, prev_state, state, myMap == initMap);
				grade_sum += ai.updateQ_table(state_index, prev_state_index, prev_action, r);
			}

			switch (action)
			{
			case 0:
				flag = dealUp();
				break;
			case 1:
				flag = dealDown();
				break;
			case 2:
				flag = dealLeft();
				break;
			case 3:
				flag = dealRight();
				break;
			default:
				dealRestart(cen, room);
			}
			if (flag)
			{
				break;
			}
			prev_state = state;
			prev_state_index = state_index;
			prev_action = action;
		}
		ai.updateQ_table(state_index, prev_state_index, prev_action,
		                 ai.getReward(myMap, prev_state, state, myMap == initMap));
		dealRestart(cen, room);
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
	change->initView = viewLastRound;
	change->finalView = viewMap->getMap();
	for (int i = 0; i <= count; i++)
	{
		change->row[i] = initRow + i * rowChange;
		change->col[i] = initCol + i * colChange;
		change->init[i] = map->getElementType(change->row[i], change->col[i]);
		if (change->init[i] == Prop::MAIN_SUB || change->init[i] == Prop::SUB_MAP)
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
				if (firstGrid->type == Prop::MAIN_SUB || change->init[i] == Prop::SUB_MAP)
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
		}
		if ((change->final[i] == Prop::SUB_MAP || change->final[i] == Prop::MAIN_SUB) && i > 0)
		{
			change->finalFather[i] = map->getSubMap(change->row[i - 1], change->col[i - 1])->outsideMap;
			change->finalSubMap[i] = map->getSubMap(change->row[i - 1], change->col[i - 1]);
		}
		else if ((map->getElementRemainsType(change->row[i], change->col[i]) == Prop::BOX_DEST) && change->final[i] ==
			Prop::BOX)
		{
			change->final[i] = Prop::HIT;
		}
		else if ((map->getElementRemainsType(change->row[i], change->col[i]) == Prop::MAN_DEST) && change->final[i] ==
			Prop::MAN)
		{
			change->final[i] = Prop::MAN_HIT;
		}
		else if (map->getElementRemainsType(change->row[i], change->col[i]) != Prop::BOX_DEST && change->final[i] ==
			Prop::HIT)
		{
			change->final[i] = Prop::BOX;
		}
		else if (map->getElementRemainsType(change->row[i], change->col[i]) != Prop::MAN_DEST && change->final[i] ==
			Prop::MAN_HIT)
		{
			change->final[i] = Prop::MAN;
		}
	}
	map->dealChange(change);
	if (!isTraining && viewMap->getMap() == map)
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
			map->getElementType(finalRow, finalCol) == Prop::SUB_MAP ||
			map->getElementType(finalRow, finalCol) == Prop::MAIN_SUB))
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
					}
					else
					{
						MapGrid grid;
						grid.map = map->getElement(backRow, backCol)->map;
						grid.type = map->getElement(backRow, backCol)->type;
						if (grid.type == Prop::MAN || grid.type == Prop::MAN_HIT)
						{
							setMap(out);
						}
						transMapMove(out, rowChange, colChange, position.row + rowChange,
						             position.col + colChange,
						             &grid, false, loop);


						if (!map->isInMap(initRow, initCol))
							ownMapMove(map, rowChange, colChange, tcount + 1, backRow, backCol, firstGrid,
							           dealingInitMap);
						else
							ownMapMove(map, rowChange, colChange, tcount, initRow, initCol, firstGrid, dealingInitMap);
						if (!isTraining && dealingInitMap && viewMap->getMap() != viewLastRound)
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
				if (map->getElementType(backRow, backCol) == Prop::SUB_MAP || map->getElementType(backRow, backCol) ==
					Prop::MAIN_SUB)
				{
					MyMap* subMap = map->getSubMap(backRow, backCol);
					if (subMap->getEntranceByMoveDirection_in(rowChange, colChange))
					{
						myPosition position = subMap->getEntrancePositionByMoveDirection_in(rowChange, colChange);
						if (subMap->canMove(rowChange, colChange, position.row, position.col, false, 0).canMove)
						{
							//subMap->outsidePosition.row = backRow;
							//subMap->outsidePosition.col = backCol;
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
								if (!isTraining && dealingInitMap && viewMap->getMap() != viewLastRound)
									viewMap->begin();
							}
							else
							{
								MapGrid grid, grid2;
								if (backRow == initRow && backCol == initCol)
								{
									grid2.map = firstGrid->map;
									grid2.type = firstGrid->type;
								}
								else
								{
									grid2.map = map->getElement(backRow - rowChange, backCol - colChange)->map;
									grid2.type = map->getElement(backRow - rowChange, backCol - colChange)->type;
								}
								if (grid2.type == Prop::MAN || grid.type == Prop::MAN_HIT)
								{
									setMap(subMap);
								}

								transMapMove(subMap, rowChange, colChange, position.row, position.col,
								             &grid2, false, loop);


								ownMapMove(map, rowChange, colChange, tcount - 1, initRow, initCol, firstGrid,
								           dealingInitMap);
								if (!isTraining && dealingInitMap)
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
	if (this->myMap->shouldCheck)
	{
		this->myMap->shouldCheck = false;
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

void MapCtrl::dealRestart(int cen, int room)
{
	MapCtrl* ctrl = this;
	MyMap* map = ctrl->initMap;
	std::stringstream ss;
	ss << "resource/map/" << cen << "." << room << ".txt";
	std::string filename = ss.str();
	map->loadMap(filename);
	ctrl->setMap(map);
	while (!ctrl->backIdStack.empty())
	{
		backIdStack.pop();
		backMapStack.pop();
		backStack.pop();
	}
	ctrl->infMap->reloadInf();
	viewMap->setMap((map));
	if (!isTraining)
		viewMap->begin();
}

void MapCtrl::dealBack()
{
	if (backIdStack.empty())return;
	const int id = backIdStack.top();
	int count = 0;
	MyMap* finalView = backStack.top()->initView;
	bool flag = true;
	while (!backIdStack.empty() && backIdStack.top() == id)
	{
		count++;
		backIdStack.pop();
		backMapStack.top()->backChange(backStack.top());
		if (viewMap->getMap() == backMapStack.top())
			viewMap->backChange(backStack.top());
		if (flag && backStack.top()->initView != nullptr)
		{
			finalView = backStack.top()->initView;
			flag = false;
		}

		backMapStack.pop();
		MyChange* change = backStack.top();
		backStack.pop();
		if (backIdStack.empty() || backIdStack.top() != id)
		{
			if (viewMap->getMap() != finalView)
			{
				myMap = finalView;
				setMap(finalView);
				if (!isTraining)
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
