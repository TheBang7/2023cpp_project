#include "MapGrid.h"
#include "myMap.h"
#include<iostream>

MapGrid::MapGrid()
{
	this->type = 0;
	this->map = nullptr;
}

void MapGrid::setMap(MyMap* map)
{
	this->map = map;
}

void MapGrid::setType(int type)
{
	this->type = type;
}

MapGrid::~MapGrid()
{
}
