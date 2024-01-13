// mapCtrl.h

#ifndef MAP_CTRL_H
#define MAP_CTRL_H

#include "myMap.h"
#include "viewMap.h"
#include "MapGrid.h"
#include <graphics.h>
#include<stack>


class ViewMap;
class MyMap;
class MyChange;
class MapGrid;

class MapCtrl
{
public:
	MapCtrl(ViewMap* viewMap);
	~MapCtrl();
	void begin();
	void dealQuit();
	void ownMapMove(MyMap* map, int rowChange, int colChange, int count, int initRow, int initCol,
	                MapGrid* firstGrid,bool isInitMap);
	void transMapMove(MyMap* map, int const rowChange, int const colChange, int initRow, int initCol,
	                  MapGrid* firstGrid,bool dealingInitMap);
	void dealUp();
	void dealDown();
	void dealLeft();
	void dealRight();

	void setMap(MyMap* map);


private:
	std::stack<MyChange*> backStack;
	ViewMap* viewMap;
	MyMap* myMap;
	int manAreaBefore;
	void dealMove(int const rowChange, int const colChange);

};

#endif // MAP_CTRL_H
