#include <iostream>
#include <random>
#include "MyMap.h"
#include<stack>
#include<queue>
#include<math.h>
#include <fstream>
#include "MapGrid.h"
#include<iostream>

MyMap::MyMap(int rows, int cols) : numRows(rows), numCols(cols), size(rows * cols)
{
	entrance = new bool[4];
	entrancePosition = new myPosition[4];
	for (int i = 0; i < 3; i++)entrance[i] = false;
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
	generate();
}

MyMap::MyMap()
{
	entrance = new bool[4];
	entrancePosition = new myPosition[4];
	for (int i = 0; i < 3; i++)entrance[i] = false;
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
	delete[]entrance;
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
				std::cout << "B ";
				break;
			case MAN:
				std::cout << "M ";
				break;
			case HIT:
				std::cout << "X ";
				break;
			default:
				std::cout << "? ";
			}
		}
		std::cout << std::endl;
	}
	// 打印地图
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			switch (mapGridRemains[i][j].type)
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
				std::cout << "B ";
				break;
			case MAN:
				std::cout << "M ";
				break;
			case HIT:
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
		if (change->final[i] == Prop::MAN)
		{
			manPositionCol = change->col[i];
			manPositionRow = change->row[i];
		}
	}
}

void MyMap::backChange(MyChange* change)
{
	for (int i = 0; i < change->all; i++)
	{
		mapGrid[change->row[i]][change->col[i]].type = change->init[i];
		mapGrid[change->row[i]][change->col[i]].map = change->initSubMap[i];
		if (change->init[i] == Prop::MAN)
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
}

void MyMap::saveMap(std::ofstream& outFile, int countSub)

{
	int t = countSub;

	// 写入地图信息到文件
	outFile << mapName << std::endl;
	outFile << numRows << " " << numCols << std::endl;
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			if (mapGrid[i][j].type != Prop::SUB_MAP)
			{
				outFile << mapGrid[i][j].type << " ";
			}
			else
			{
				mapGrid[i][j].map->setMapName("Sub_Map_" + std::to_string(t));
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
			if (mapGrid[i][j].type == Prop::SUB_MAP)
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
		return;
	}
	if (hasMapGrid)
	{
		for (int i = 0; i < numRows; ++i)
		{
			delete[] mapGrid[i];
		}
		delete[] mapGrid;
	}
	int rows, cols;
	std::string name, mainName;
	// 读取地图信息
	bool flag = true;
	while (inFile >> name)
	{
		inFile >> rows >> cols;
		MyMap* mapPtr;
		if (flag)
		{
			mapPtr = this;
			numRows = rows;
			numCols = cols;
			for (int i = 0; i < 3; i++)entrance[i] = false;
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
			std::cout << mapPtr->getNumRows() << "   " << mapPtr->getNumCols() << std::endl;
		}
		mapPtr->setMapName(name);

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				std::string type;
				inFile >> type;
				if (type.compare(0, 8, "Sub_Map_") == 0)
				{
					// 执行相应的操作
					mapPtr->setGridType(i, j, Prop::SUB_MAP);
					mapPtr->setSubMapName(i, j, type);
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
					if (((i == 0 || i == numRows - 1) && (j != 0 && j != numCols - 1) ||
							(i != 0 && i != numRows - 1) && (j == 0 || j == numCols - 1))
						&& typeValue == Prop::FLOOR)
					{
						if (i == 0)
						{
							if (mapPtr->entrance[0]) // 如果已经为true，抛出异常
							{
								throw std::runtime_error("Map Entrance ERROR!");
							}
							mapPtr->entrance[0] = true;
							mapPtr->entrancePosition[0].row = i;
							mapPtr->entrancePosition[0].col = j;
						}
						else if (i == numRows - 1)
						{
							if (mapPtr->entrance[1]) // 如果已经为true，抛出异常
							{
								throw std::runtime_error("Map Entrance ERROR!");
							}
							mapPtr->entrance[1] = true;
							mapPtr->entrancePosition[1].row = i;
							mapPtr->entrancePosition[1].col = j;
						}
						else if (j == 0)
						{
							if (mapPtr->entrance[2]) // 如果已经为true，抛出异常
							{
								throw std::runtime_error("Map Entrance ERROR!");
							}
							mapPtr->entrance[2] = true;
							mapPtr->entrancePosition[2].row = i;
							mapPtr->entrancePosition[2].col = j;
						}
						else
						{
							if (mapPtr->entrance[3]) // 如果已经为true，抛出异常
							{
								throw std::runtime_error("Map Entrance ERROR!");
							}
							mapPtr->entrance[3] = true;
							mapPtr->entrancePosition[3].row = i;
							mapPtr->entrancePosition[3].col = j;
						}
					}
				}
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


	for (auto it : hashMap)
	{
		std::string mapName = it.first;
		MyMap* mapPtr = it.second;
		for (int i = 0; i < mapPtr->getNumRows(); i++)
			for (int j = 0; j < mapPtr->getNumCols(); j++)
			{
				if (mapPtr->getElementType(i, j) == Prop::SUB_MAP)
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
	subMap->outsideMap = this;
	subMap->outsidePosition.row = row;
	subMap->outsidePosition.col = col;
}

std::string MyMap::getSubMapNameToSet(int row, int col)
{
	return mapGrid[row][col].subMapName;
}

bool MyMap::getEntranceByMoveDirection(int rowChange, int colChange)
{
	if (rowChange == 1 && colChange == 0)return entrance[0];
	else if (rowChange == -1 && colChange == 0)return entrance[1];
	else if (rowChange == 0 && colChange == 1)return entrance[2];
	else if (rowChange == 0 && colChange == -1)return entrance[3];
	return false;
}

myPosition MyMap::getEntrancePositionByMoveDirection(int rowChange, int colChange)
{
	if (rowChange == 1 && colChange == 0)return entrancePosition[0];
	else if (rowChange == -1 && colChange == 0)return entrancePosition[1];
	else if (rowChange == 0 && colChange == 1)return entrancePosition[2];
	else return entrancePosition[3];
}

bool MyMap::canMove(int const rowChange, int const colChange, int const initRow, int const initCol)
{
	MyMap* myMap = this;
	int count = 1;
	int finalRow = initRow + rowChange;
	int finalCol = initCol + colChange;
	while (myMap->isInMap(finalRow, finalCol) &&
		(myMap->getElementType(finalRow, finalCol) == Prop::BOX ||
			myMap->getElementType(finalRow, finalCol) == Prop::HIT) ||
		myMap->getElementType(finalRow, finalCol) == Prop::SUB_MAP)
	{
		count++;
		finalCol += colChange;
		finalRow += rowChange;
	}
	if (!myMap->isInMap(finalRow, finalCol) || myMap->getElementType(finalRow, finalCol) == Prop::WALL)
	{
		int backRow = finalRow;
		int backCol = finalCol;
		for (int i = 1; i <= count; i++)
		{
			if (myMap->getElementType(backRow, backCol) == Prop::SUB_MAP)
			{
				MyMap* subMap = myMap->getSubMap(backRow, backCol);
				if (subMap->getEntranceByMoveDirection(rowChange, colChange))
				{
					myPosition position = subMap->getEntrancePositionByMoveDirection(rowChange, colChange);
					if (subMap->canMove(rowChange, colChange, position.row, position.col))return true;
				}
			}
			backCol -= colChange;
			backRow -= rowChange;
		}
		return false;
	}
	else
	{
		return true;
	}
}
