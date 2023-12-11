// mapCtrl.h

#ifndef MAP_CTRL_H
#define MAP_CTRL_H

#include "myMap.h"


class ViewMap;

class MapCtrl
{
public:
	MapCtrl(ViewMap* viewMap);
	void begin();

private:
	static constexpr char key_up = 'w';
	static constexpr char key_down = 's';
	static constexpr char key_left = 'a';
	static constexpr char key_right = 'd';
	static constexpr char key_quit = 'q';
	ViewMap* viewMap;
	static void dealQuit();
	static void dealUp();
	static void dealDown();
	static void dealLeft();
	static void dealRight();
};

#endif // MAP_CTRL_H
