// mapCtrl.h

#ifndef MAP_CTRL_H
#define MAP_CTRL_H

#include "myMap.h"
#include <graphics.h>
#include<stack>


class ViewMap;

class MapCtrl
{
public:
	MapCtrl(ViewMap* viewMap);
	~MapCtrl();
	void begin();
	void dealQuit();
	void dealUp();
	void dealDown();
	void dealLeft();
	void dealRight();

private:

	std::stack<MyChange*> backStack;
	ViewMap* viewMap;
	MyMap* myMap;
	int manAreaBefore;
	void dealMove(int const rowChange,int const colChange);
};

#endif // MAP_CTRL_H
