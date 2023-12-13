#ifndef MY_MAP_GRID_H
#define MY_MAP_GRID_H
#include "myMap.h"

class MyMap;

class MapGrid
{
private:
public:
	int type;
	MyMap* map;
	MapGrid();
	void setMap(MyMap* map);
	void setType(int type);
};
#endif
