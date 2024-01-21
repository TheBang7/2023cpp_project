#include <iostream>
#include <random>
#include "MyMap.h"
#include<stack>
#include<queue>
#include<math.h>
#include <fstream>
#include "MapGrid.h"
#include<iostream>
#include<windows.h>


MyMap::MyMap(int rows, int cols) : numRows(rows), numCols(cols), size(rows * cols)
{
	manPositionCol = 0;
	manPositionRow = 0;
	outsideMap = nullptr;
	outsidePosition.row = 0;
	outsidePosition.col = 0;
	entrancePosition = new myPosition[4];
	for (int i = 0; i <= 3; i++)entrance[i] = false;
	mapGrid = new MapGrid*[numRows];
	for (int i = 0; i < numRows; ++i)
	{
		mapGrid[i] = new MapGrid[numCols];
	}
	mapGridRemains = new MapGrid*[numRows];
	for (int i = 0; i < numRows; ++i)
	{
		mapGridRemains[i] = new MapGrid[numCols];
	}
	hasMapGrid = true;
	//generate();
}

MyMap::MyMap()
{
	entrancePosition = new myPosition[4];
	for (int i = 0; i <= 3; i++)entrance[i] = false;
	manPositionCol = 0;
	manPositionRow = 0;

	numCols = 10;
	numRows = 10;
	size = 100;
	mapGrid = new MapGrid*[numRows];
	for (int i = 0; i < numRows; ++i)
	{
		mapGrid[i] = new MapGrid[numCols];
	}
	mapGridRemains = new MapGrid*[numRows];
	for (int i = 0; i < numRows; ++i)
	{
		mapGridRemains[i] = new MapGrid[numCols];
	}
	hasMapGrid = true;
	// 初始化随机数生成器
	std::random_device seed;
	std::ranlux48 gen(seed());

	// 全部初始化为 FLOOR
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			if (i == 0 || j == 0 || i == numRows - 1 || j == numCols - 1)
				mapGrid[i][j].type = Prop::WALL;
			else
				mapGrid[i][j].type = Prop::FLOOR;
		}
	}
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			mapGridRemains[i][j] = mapGrid[i][j];
		}
	}
}

void MyMap::reloadInf()
{
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			if (i == 0 || j == 0 || i == numRows - 1 || j == numCols - 1)
				mapGrid[i][j].type = Prop::WALL;
			else
				mapGrid[i][j].type = Prop::FLOOR;
		}
	}
}

MyMap::MyMap(bool isInf)
{
	this->isInf = true;
	if (isInf)
	{
		entrancePosition = new myPosition[4];
		for (int i = 0; i <= 3; i++)entrance[i] = true;
		manPositionCol = 0;
		manPositionRow = 0;

		numCols = 7;
		numRows = 7;
		size = 25;
		mapGrid = new MapGrid*[numRows];
		for (int i = 0; i < numRows; ++i)
		{
			mapGrid[i] = new MapGrid[numCols];
		}
		mapGridRemains = new MapGrid*[numRows];
		for (int i = 0; i < numRows; ++i)
		{
			mapGridRemains[i] = new MapGrid[numCols];
		}
		hasMapGrid = true;


		for (int i = 0; i < numRows; ++i)
		{
			for (int j = 0; j < numCols; ++j)
			{
				if (i == 0 || j == 0 || i == numRows - 1 || j == numCols - 1)
					mapGrid[i][j].type = Prop::WALL;
				else
					mapGrid[i][j].type = Prop::FLOOR;
			}
		}
		for (int i = 0; i < numRows; ++i)
		{
			for (int j = 0; j < numCols; ++j)
			{
				mapGridRemains[i][j] = mapGrid[i][j];
			}
		}
		entrancePosition[0].row = 0;
		entrancePosition[0].col = 3;
		entrancePosition[1].row = 0;
		entrancePosition[1].col = 3;
		entrancePosition[2].row = 3;
		entrancePosition[2].col = 0;
		entrancePosition[3].row = 3;
		entrancePosition[3].col = 6;
	}
	else MyMap();
}


int MyMap::getNumRows()
{
	return numRows;
}

int MyMap::getNumCols()
{
	return numCols;
}

int MyMap::getElementType(int x, int y)
{
	return mapGrid[x][y].type;
}

MapGrid* MyMap::getElement(int x, int y)
{
	return &mapGrid[x][y];
}

int MyMap::getElementRemainsType(int x, int y)
{
	return mapGridRemains[x][y].type;
}

void MyMap::generate()
{
	// 初始化随机数生成器
	std::random_device seed;
	std::ranlux48 gen(seed());

	// 全部初始化为 FLOOR
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			if (i == 0 || j == 0 || i == numRows - 1 || j == numCols - 1)
				mapGrid[i][j].type = Prop::WALL;
			else
				mapGrid[i][j].type = Prop::FLOOR;
		}
	}

	// 随机生成 WALL 的数量
	std::uniform_int_distribution<> disWall(size / 20, size / 15);
	std::uniform_int_distribution<> posRow(2, numRows - 3);
	std::uniform_int_distribution<> posCol(2, numCols - 3);

	int numWalls = disWall(gen);
	int row, col;

	// 随机生成 WALL
	for (int i = 0; i < numWalls; ++i)
	{
		row = posRow(gen) % numRows;
		col = posCol(gen) % numCols;
		mapGrid[row][col].type = Prop::WALL;
	}

	// 随机生成 BOX_DEST 和 BOX 的数量
	std::uniform_int_distribution<> disBox(1, 5);
	int numBoxDest = disBox(gen);
	int numBox = numBoxDest;


	// 随机生成 BOX_DEST
	for (int i = 0; i < numBoxDest; ++i)
	{
		do
		{
			row = posRow(gen) % numRows;
			col = posCol(gen) % numCols;
		}
		while (mapGrid[row][col].type != Prop::FLOOR);
		mapGrid[row][col].type = Prop::BOX_DEST;
	}

	// 随机生成 BOX
	for (int i = 0; i < numBox; ++i)
	{
		do
		{
			row = posRow(gen) % numRows;
			col = posCol(gen) % numCols;
		}
		while (mapGrid[row][col].type != Prop::FLOOR);
		mapGrid[row][col].type = Prop::BOX;
	}
	//随机生成MAN
	do
	{
		row = posRow(gen) % numRows;
		col = posCol(gen) % numCols;
	}
	while (mapGrid[row][col].type != Prop::FLOOR);
	this->manPositionCol = col;
	this->manPositionRow = row;
	mapGrid[row][col].type = Prop::MAN;
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			mapGridRemains[i][j] = mapGrid[i][j];
		}
	}
}

MyMap::~MyMap()
{
	delete[]entrancePosition;
	for (int i = 0; i < numRows; ++i)
	{
		delete[] mapGrid[i];
	}
	delete[] mapGrid;
}

int MyMap::getManPositionCol()
{
	return this->manPositionCol;
}

int MyMap::getManPositionRow()
{
	return this->manPositionRow;
}


void MyMap::printMap()
{
	// 打印地图
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			switch (mapGrid[i][j].type)
			{
			case WALL:
				std::cout << "# ";
				break;
			case FLOOR:
				std::cout << ". ";
				break;
			case BOX_DEST:
				std::cout << "D ";
				break;
			case BOX:
				std::cout << "O ";
				break;
			case MAN:
				std::cout << "P ";
				break;
			case MAN_DEST:
				std::cout << "= ";
				break;
			case MAN_HIT:
				std::cout << "p ";
				break;
			case HIT:
				std::cout << "o";
				break;
			case SUB_MAP:
				std::cout << "X ";
				break;
			default:
				std::cout << "? ";
			}
		}
		std::cout << std::endl;
	}
}

void MyMap::dealChange(MyChange* change)
{
	for (int i = 0; i < change->all; i++)
	{
		mapGrid[change->row[i]][change->col[i]].type = change->final[i];
		mapGrid[change->row[i]][change->col[i]].map = change->finalSubMap[i];
		if (change->final[i] == Prop::MAIN_SUB)
		{
			change->finalSubMap[i]->outsidePosition.row = change->row[i];
			change->finalSubMap[i]->outsidePosition.col = change->col[i];
			change->finalSubMap[i]->outsideMap = change->finalFather[i];
		}
		if (change->final[i] == Prop::MAN || change->final[i] == Prop::MAN_HIT)
		{
			manPositionCol = change->col[i];
			manPositionRow = change->row[i];
			if (change->final[i] == Prop::MAN_HIT)
			{
				shouldCheck = true;
			}
		}
	}
}

void MyMap::backChange(MyChange* change)
{
	for (int i = 0; i < change->all; i++)
	{
		mapGrid[change->row[i]][change->col[i]].type = change->init[i];
		mapGrid[change->row[i]][change->col[i]].map = change->initSubMap[i];
		if (change->init[i] == Prop::MAIN_SUB)
		{
			change->initSubMap[i]->outsidePosition.row = change->row[i];
			change->initSubMap[i]->outsidePosition.col = change->col[i];
			change->initSubMap[i]->outsideMap = change->initFather[i];
		}
		if (change->init[i] == Prop::MAN || change->init[i] == Prop::MAN_HIT)
		{
			manPositionCol = change->col[i];
			manPositionRow = change->row[i];
		}
	}
}

bool MyMap::isInMap(int row, int col)
{
	return (row >= 0 && row < this->getNumRows() && col >= 0 && col < this->getNumCols());
}

MyMap* MyMap::getSubMap(int row, int col)
{
	return mapGrid[row][col].map;
}

std::string MyMap::getMapName()
{
	return mapName;
}

void MyMap::setMapName(std::string name)
{
	mapName = name;
}

void MyMap::saveMap(std::string address)
{
	// 打开文件
	std::ofstream outFile;
	outFile.open(address);

	// 如果打开失败，尝试创建文件
	if (!outFile.is_open())
	{
		std::cerr << "无法打开文件" << address << "，尝试创建文件并保存地图" << std::endl;

		// 创建文件
		outFile.open(address, std::ofstream::out | std::ofstream::trunc);

		// 再次检查是否成功
		if (!outFile.is_open())
		{
			std::cerr << "无法创建文件" << address << "，保存地图失败" << std::endl;
			return;
		}
	}
	saveMap(outFile, 0);
	std::cout << "map saved: " + address << std::endl;
	// 关闭文件
	outFile.close();
	for (MyMap* map : mapList)
	{
		map->printed = false;
	}
	printed = false;
}

void MyMap::saveMap(std::ofstream& outFile, int countSub)

{
	int t = countSub;
	this->printed = true;

	// 写入地图信息到文件
	outFile << mapName << std::endl;
	outFile << numRows << " " << numCols << std::endl;
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			if (mapGrid[i][j].type != Prop::SUB_MAP && mapGrid[i][j].type != Prop::MAIN_SUB)
			{
				outFile << mapGrid[i][j].type << " ";
			}
			else
			{
				outFile << mapGrid[i][j].map->getMapName() << " ";
				t++;
			}
		}
		outFile << std::endl;
	}
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			outFile << mapGridRemains[i][j].type << " ";
		}
		outFile << std::endl;
	}
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			if (mapGrid[i][j].type == Prop::SUB_MAP || mapGrid[i][j].type == Prop::MAIN_SUB && !mapGrid[i][j].map->
				printed)
			{
				mapGrid[i][j].map->saveMap(outFile, t);
			}
		}
	}
}

void MyMap::setGridType(int row, int col, int type)
{
	mapGrid[row][col].setType(type);
}

void MyMap::setSubMapName(int row, int col, std::string name)
{
	mapGrid[row][col].subMapName = name;
}

void MyMap::loadMap(std::string address)
{
	// 打开文件
	std::ifstream inFile(address);

	if (!inFile.is_open())
	{
		std::cerr << "无法打开文件" << address << "来加载地图" << std::endl;
	}
	if (hasMapGrid)
	{
		for (int i = 0; i < numRows; ++i)
		{
			delete[] mapGrid[i];
		}
		delete[] mapGrid;
	}
	for (MyMap* map : mapList)
	{
		delete map;
	}
	mapList.clear();
	hashMap.clear();
	int rows, cols;
	std::string name, mainName;
	// 读取地图信息
	bool flag = true;
	try
	{
		while (inFile >> name)
		{
			inFile >> rows >> cols;
			MyMap* mapPtr;
			if (flag)
			{
				mapPtr = this;
				numRows = rows;
				numCols = cols;
				for (int i = 0; i <= 3; i++)entrance[i] = false;
				mapGrid = new MapGrid*[numRows];
				for (int i = 0; i < this->numRows; ++i)
				{
					mapGrid[i] = new MapGrid[numCols];
				}
				mapGridRemains = new MapGrid*[numRows];
				for (int i = 0; i < this->numRows; ++i)
				{
					mapGridRemains[i] = new MapGrid[numCols];
				}


				flag = false;
			}
			else
			{
				mapPtr = new MyMap(rows, cols);
				mapList.push_back(mapPtr);
			}
			mapPtr->setMapName(name);
			std::vector<myPosition> top;
			std::vector<myPosition> down;
			std::vector<myPosition> left;
			std::vector<myPosition> right;

			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					std::string type;
					inFile >> type;
					bool isSingleDigit = true;
					for (char ch : type)
					{
						if (!std::isdigit(ch))
						{
							isSingleDigit = false;
							break;
						}
					}
					if (!isSingleDigit)
					{
						if (type.find("MAIN::") == 0)
						{
							mapPtr->setGridType(i, j, Prop::MAIN_SUB);
							mapPtr->setSubMapName(i, j, type.substr(6));
						}

						else
						{
							mapPtr->setGridType(i, j, Prop::SUB_MAP);
							mapPtr->setSubMapName(i, j, type);
						}

						//mapPtr->setSubMap(i,j,mapPtr);
					}
					else
					{
						int typeValue = std::stoi(type);
						if (typeValue >= Prop::ALL)
						{
							throw std::out_of_range("Invalid Map File: MapGrid ERROR !");
						}
						else if (typeValue == Prop::MAN)
						{
							mapPtr->manPositionCol = j;
							mapPtr->manPositionRow = i;
						}
						mapPtr->setGridType(i, j, typeValue);
						if (((i == 0 || i == rows - 1) && (j != 0 && j != cols - 1) ||
								(i != 0 && i != rows - 1) && (j == 0 || j == cols - 1))
							&& typeValue != Prop::WALL)
						{
							if (i == 0)
							{
								mapPtr->entrance[0] = true;
								myPosition p;
								p.row = i;
								p.col = j;
								top.push_back(p);
							}
							else if (i == rows - 1)
							{
								mapPtr->entrance[1] = true;
								myPosition p;
								p.row = i;
								p.col = j;
								down.push_back(p);
							}
							else if (j == 0)
							{
								mapPtr->entrance[2] = true;
								myPosition p;
								p.row = i;
								p.col = j;
								left.push_back(p);
							}
							else if (j == cols - 1)
							{
								mapPtr->entrance[3] = true;
								myPosition p;
								p.row = i;
								p.col = j;
								right.push_back(p);
							}
						}
					}
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (mapPtr->entrance[i])
				{
					if (i == 0)
						mapPtr->entrancePosition[i] = top[top.size() / 2];
					else if (i == 1)
						mapPtr->entrancePosition[i] = down[down.size() / 2];
					else if (i == 2)
						mapPtr->entrancePosition[i] = left[left.size() / 2];
					else
						mapPtr->entrancePosition[i] = right[right.size() / 2];
				}
			}

			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					std::string type;
					inFile >> type;

					int typeValue = std::stoi(type);
					if (typeValue >= Prop::ALL)
					{
						throw std::out_of_range("Invalid Map File: MapGrid ERROR !");
					}
					mapPtr->mapGridRemains[i][j].type = typeValue;
				}
			}


			hashMap.insert({mapPtr->getMapName(), mapPtr});
		}
	}
	catch (const std::exception& e)
	{
		MessageBox(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
		inFile.close();
		return;
	}


	for (auto it : hashMap)
	{
		std::string mapName = it.first;
		MyMap* mapPtr = it.second;
		for (int i = 0; i < mapPtr->getNumRows(); i++)
			for (int j = 0; j < mapPtr->getNumCols(); j++)
			{
				if (mapPtr->getElementType(i, j) == Prop::SUB_MAP || mapPtr->getElementType(i, j) == Prop::MAIN_SUB)
				{
					if (hashMap.find(mapPtr->getSubMapNameToSet(i, j)) != hashMap.end())
					{
						MyMap* t = hashMap.find(mapPtr->getSubMapNameToSet(i, j))->second;
						mapPtr->setSubMap(i, j, t);
					}
					else
						throw std::out_of_range("Invalid Map File: SubMap ERROR !");
				}
			}
	}

	// 关闭文件
	inFile.close();
}

void MyMap::setSubMap(int row, int col, MyMap* subMap)
{
	mapGrid[row][col].setMap(subMap);
	if (mapGrid[row][col].type == Prop::MAIN_SUB)
	{
		subMap->outsideMap = this;
		subMap->outsidePosition.row = row;
		subMap->outsidePosition.col = col;
	}
}

std::string MyMap::getSubMapNameToSet(int row, int col)
{
	return mapGrid[row][col].subMapName;
}

bool MyMap::getEntranceByMoveDirection_out(int rowChange, int colChange)
{
	if (rowChange == -1 && colChange == 0)return entrance[0];
	else if (rowChange == 1 && colChange == 0)return entrance[1];
	else if (rowChange == 0 && colChange == -1)return entrance[2];
	else if (rowChange == 0 && colChange == 1)return entrance[3];
	return false;
}

bool MyMap::getEntranceByMoveDirection_in(int rowChange, int colChange)
{
	if (rowChange == 1 && colChange == 0)return entrance[0];
	else if (rowChange == -1 && colChange == 0)return entrance[1];
	else if (rowChange == 0 && colChange == 1)return entrance[2];
	else if (rowChange == 0 && colChange == -1)return entrance[3];
	return false;
}

myPosition MyMap::getEntrancePositionByMoveDirection_out(int rowChange, int colChange)
{
	if (rowChange == -1 && colChange == 0)return entrancePosition[0];
	else if (rowChange == 1 && colChange == 0)return entrancePosition[1];
	else if (rowChange == 0 && colChange == -1)return entrancePosition[2];
	else return entrancePosition[3];
}

myPosition MyMap::getEntrancePositionByMoveDirection_in(int rowChange, int colChange)
{
	if (rowChange == 1 && colChange == 0)return entrancePosition[0];
	else if (rowChange == -1 && colChange == 0)return entrancePosition[1];
	else if (rowChange == 0 && colChange == 1)return entrancePosition[2];
	else return entrancePosition[3];
}

moveInfo MyMap::canMove(int const rowChange, int const colChange, int const initRow, int const initCol,
                        bool loop = false,
                        int countInf = 0)
{
	moveInfo info;
	if (countInf >= 10)
	{
		info.canMove = false;
		info.shouldInf = true;
		return info;
	}
	else
	{
		bool flag = false;
		MyMap* myMap = this;
		if (myMap == nullptr)
		{
			info.canMove = false;
			info.shouldInf = false;
			return info;
		}
		int count = 1;
		int finalRow = initRow;
		int finalCol = initCol;
		while (myMap->isInMap(finalRow, finalCol) &&
			(myMap->getElementType(finalRow, finalCol) == Prop::BOX ||
				myMap->getElementType(finalRow, finalCol) == Prop::MAN ||
				myMap->getElementType(finalRow, finalCol) == Prop::MAN_HIT ||
				myMap->getElementType(finalRow, finalCol) == Prop::HIT ||
				myMap->getElementType(finalRow, finalCol) == Prop::SUB_MAP ||
				myMap->getElementType(finalRow, finalCol) == Prop::MAIN_SUB))
		{
			if (myMap->getElementType(finalRow, finalCol) == Prop::MAN)
			{
				if (loop)
				{
					info.canMove = true;
					return info;
				}
				flag = true;
			} //连续两次碰到人所在的位置，代表路径为环
			count++;
			finalCol += colChange;
			finalRow += rowChange;
		}
		if (!myMap->isInMap(finalRow, finalCol) || myMap->getElementType(finalRow, finalCol) == Prop::WALL)
		{
			int backRow = finalRow;
			int backCol = finalCol;

			if (!myMap->isInMap(finalRow, finalCol))
			{
				backCol -= colChange;
				backRow -= rowChange;
				if (myMap->getEntranceByMoveDirection_out(rowChange, colChange))
				{
					myPosition position = myMap->outsidePosition;
					moveInfo tinfo = outsideMap->canMove(rowChange, colChange, position.row + colChange,
					                                     position.col + colChange,
					                                     flag, countInf + 1);
					if (tinfo.canMove)
					{
						info.canMove = true;
						return info;
					}
					else if (tinfo.shouldInf)
					{
						info.shouldInf = true;
						return info;
					}
				}
			}
			else
			{
				for (int i = 1; i <= count; i++)
				{
					if (myMap->getElementType(backRow, backCol) == Prop::SUB_MAP || myMap->getElementType(
						backRow, backCol) == Prop::MAIN_SUB)
					{
						MyMap* subMap = myMap->getSubMap(backRow, backCol);
						if (subMap->getEntranceByMoveDirection_in(rowChange, colChange))
						{
							myPosition position = subMap->getEntrancePositionByMoveDirection_in(rowChange, colChange);
							moveInfo tinfo = subMap->canMove(rowChange, colChange, position.row, position.col, flag,
							                                 countInf + 1);
							if (tinfo.canMove)
							{
								info.canMove = true;
								return info;
							}
							else if (tinfo.shouldInf)
							{
								info.shouldInf = true;
								return info;
							}
						}
					}
					backCol -= colChange;
					backRow -= rowChange;
				}
			}
			return info;
		}
		else
		{
			info.canMove = true;
			return info;
		}
	}
}


bool MyMap::loopMove(int const rowChange, int const colChange, int const initRow, int const initCol, bool loop = false,
                     int countInf = 0)
{
	if (countInf >= 10 || !canMove(rowChange, colChange, initRow, initCol).canMove)return false;
	bool flag = false;
	MyMap* myMap = this;
	int count = 0;
	int finalRow = initRow;
	int finalCol = initCol;
	while (myMap->isInMap(finalRow, finalCol) &&
		(myMap->getElementType(finalRow, finalCol) == Prop::BOX ||
			myMap->getElementType(finalRow, finalCol) == Prop::MAN ||
			myMap->getElementType(finalRow, finalCol) == Prop::HIT ||
			myMap->getElementType(finalRow, finalCol) == Prop::SUB_MAP ||
			myMap->getElementType(finalRow, finalCol) == Prop::MAIN_SUB))
	{
		if (myMap->getElementType(finalRow, finalCol) == Prop::MAN)
		{
			if (loop)return true;
			flag = true;
		} //连续两次碰到人所在的位置，代表路径为环
		count++;
		finalCol += colChange;
		finalRow += rowChange;
	}
	if (!myMap->isInMap(finalRow, finalCol) || myMap->getElementType(finalRow, finalCol) == Prop::WALL)
	{
		int backRow = finalRow;
		int backCol = finalCol;

		if (!myMap->isInMap(finalRow, finalCol))
		{
			if (myMap->getEntranceByMoveDirection_out(rowChange, colChange))
			{
				myPosition position = myMap->outsidePosition;
				if (outsideMap->loopMove(rowChange, colChange, position.row + rowChange, position.col + colChange,
				                         flag, countInf + 1))
				{
					return true;
				}
			}
		}
		else
		{
			for (int i = 1; i <= count; i++)
			{
				backCol -= colChange;
				backRow -= rowChange;
				if (myMap->getElementType(backRow, backCol) == Prop::SUB_MAP || myMap->getElementType(backRow, backCol)
					== Prop::MAIN_SUB)
				{
					MyMap* subMap = myMap->getSubMap(backRow, backCol);
					if (subMap->getEntranceByMoveDirection_in(rowChange, colChange))
					{
						myPosition position = subMap->getEntrancePositionByMoveDirection_in(rowChange, colChange);
						if (subMap->loopMove(rowChange, colChange, position.row, position.col, flag, countInf + 1))
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

bool MyMap::checkMap()
{
	std::vector<MyMap*> list;
	list.push_back(this);
	bool flag = checkMap(list);
	for (auto t : list)
		t->checked = false;
	return flag;
}

bool MyMap::checkMap(std::vector<MyMap*>& list)
{
	this->checked = true;

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			if (mapGrid[i][j].type == Prop::BOX_DEST || mapGrid[i][j].type == Prop::MAN_DEST || mapGrid[i][j].
				type != Prop::MAN_HIT && mapGridRemains[i][j].type == Prop::MAN_DEST)
				return false;
			if (mapGrid[i][j].type == Prop::SUB_MAP || mapGrid[i][j].type == Prop::MAIN_SUB)
			{
				if (!mapGrid[i][j].map->checked)
				{
					mapGrid[i][j].map->checked = true;
					list.push_back(mapGrid[i][j].map);
					bool flag = mapGrid[i][j].map->checkMap(list);
					if (!flag) return false;
				}
			}
		}
	}
	return true;
}
