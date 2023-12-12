#include <iostream>
#include <random>
#include "MyMap.h"
#include<stack>
#include<queue>
#include<math.h>


MyMap::MyMap(int rows, int cols) : numRows(rows), numCols(cols), size(rows * cols)
{
	mapGrid = new int*[numRows];
	for (int i = 0; i < numRows; ++i)
	{
		mapGrid[i] = new int[numCols];
	}
	generate();
}

MyMap::MyMap()
{
	MyMap(10, 10);
}

int MyMap::getNumRows()
{
	return numRows;
}

int MyMap::getNumCols()
{
	return numCols;
}

int MyMap::getElement(int x, int y)
{
	return mapGrid[x][y];
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
				mapGrid[i][j] = Prop::WALL;
			else
				mapGrid[i][j] = Prop::FLOOR;
		}
	}

	// 随机生成 WALL 的数量
	std::uniform_int_distribution<> disWall(size / 8, size / 5);
	std::uniform_int_distribution<> posRow(0, numRows - 1);
	std::uniform_int_distribution<> posCol(0, numCols - 1);

	int numWalls = disWall(gen);
	int row, col;

	// 随机生成 WALL
	for (int i = 0; i < numWalls; ++i)
	{
		row = posRow(gen) % numRows;
		col = posCol(gen) % numCols;
		mapGrid[row][col] = Prop::WALL;
	}

	// 随机生成 BOX_DEST 和 BOX 的数量
	std::uniform_int_distribution<> disBox(std::max(1, size / 30), std::max(1, size / 20));
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
		while (mapGrid[row][col] != Prop::FLOOR);
		mapGrid[row][col] = Prop::BOX_DEST;
	}

	// 随机生成 BOX
	for (int i = 0; i < numBox; ++i)
	{
		do
		{
			row = posRow(gen) % numRows;
			col = posCol(gen) % numCols;
		}
		while (mapGrid[row][col] != Prop::FLOOR);
		mapGrid[row][col] = Prop::BOX;
	}
	//随机生成MAN
	do
	{
		row = posRow(gen) % numRows;
		col = posCol(gen) % numCols;
	}
	while (mapGrid[row][col] != Prop::FLOOR);
	this->manPositionCol = col;
	this->manPositionRow = row;
	mapGrid[row][col] = Prop::MAN;
}

MyMap::~MyMap()
{
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
			switch (mapGrid[i][j])
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

void MyMap::dealChange(Change change)
{
	for (int i = 0; i < change.all; i++)
	{
		mapGrid[change.row[i]][change.col[i]] = change.final[i];
		if (change.final[i] == Prop::MAN)
		{
			manPositionCol = change.col[i];
			manPositionRow = change.row[i];
		}
	}
}

void MyMap::backChange(Change change)
{
	for (int i = 0; i < change.all; i++)
	{
		mapGrid[change.row[i]][change.col[i]] = change.init[i];
		if (change.init[i] == Prop::MAN)
		{
			manPositionCol = change.col[i];
			manPositionRow = change.row[i];
		}
	}
}

bool MyMap::isInMap(int row, int col)
{
	return (row >= 0 && row < this->getNumRows() && col >= 0 && col < this->getNumCols());
}
