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
	void begin();

private:
	static constexpr char key_up = 'W';
	static constexpr char key_down = 'S';
	static constexpr char key_left = 'A';
	static constexpr char key_right = 'D';
	static constexpr char key_quit = VK_ESCAPE;
	std::stack<MyChange> backStack;
	ViewMap* viewMap;
	MyMap* myMap;
	int manAreaBefore;
	void dealQuit();
	void dealUp();
	void dealDown();
	void dealLeft();
	void dealRight();
	void dealMove(int const rowChange,int const colChange);
};

#endif // MAP_CTRL_H
