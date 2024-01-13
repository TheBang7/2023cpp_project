//viewMap.h
#ifndef VIEW_MAP_H
#define VIEW_MAP_H
#include <graphics.h>

#include "myMap.h"
#include "myChange.h"


class ViewMap
{
private:
	void init_picture();
	MyMap* map;
	IMAGE background, subBackground;
	IMAGE* props;
	IMAGE* subProps;
	static constexpr int ScreenWidth = 1250;
	static constexpr int StartY = 50;
	static constexpr int ScreenHeight = 1000;
	int ratio, subRatio, StartX = 100;
	void updateProp(MyMap* map, int row, int col);
	void updatePropByChange(int row, int col, int prop);
	void loadSubMapPicture(MyMap* subMap);

public:
	ViewMap(MyMap* map);
	~ViewMap();
	void begin();
	void printSubMap(MyMap* map, int row, int col);
	void printMap(MyMap* map);
	void quitView();
	MyMap* getMap();
	void dealChange(MyChange* change);
	void backChange(MyChange* change);
	void setMap(MyMap* map);
};

#endif
