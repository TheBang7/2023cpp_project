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
constexpr char key_up = 'W';
constexpr char key_down = 'S';
constexpr char key_left = 'A';
constexpr char key_right = 'D';
constexpr char key_quit = '0';
constexpr char key_restart = 'R';
constexpr char key_pause = VK_ESCAPE;
constexpr char key_back = 'Q';

class MapCtrl
{
public:
	MapCtrl(ViewMap* viewMap, MyMap* infMap);
	~MapCtrl();
	void begin(int& cen,int& room,int& ifload);
	void dealQuit();
	void ownMapMove(MyMap* map, int rowChange, int colChange, int count, int initRow, int initCol,
	                MapGrid* firstGrid, bool isInitMap);
	void transMapMove(MyMap* map, int const rowChange, int const colChange, int initRow, int initCol,
	                  MapGrid* firstGrid, bool dealingInitMap, bool loopTrans);
	bool dealUp();
	bool dealDown();
	bool dealLeft();
	bool dealRight();
	void setMap(MyMap* map);
	void dealBack();
	MyMap* getMap();
	MyMap* infMap;
	MyMap* initMap;
	bool isTraining=false;

private:

	std::stack<MyChange*> backStack;
	std::stack<MyMap*> backMapStack;
	std::stack<int> backIdStack;
	ViewMap* viewMap;
	MyMap* myMap;
	int manAreaBefore;
	bool dealMove(int const rowChange, int const colChange);
	int countInf = 0; //大于十次算作死循环
	const int maxInf = 10;
	int countStep = 0;
	MyMap* mainMap;
};

#endif // MAP_CTRL_H
