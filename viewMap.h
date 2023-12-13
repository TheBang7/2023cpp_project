//viewMap.h
#ifndef VIEW_MAP_H
#define VIEW_MAP_H
#include <graphics.h>

#include "mapCtrl.h"
#include "myMap.h"
#include "myChange.h"


class ViewMap
{
private:
	void init_picture();
	MyMap* map;
	IMAGE background,subBackground;
	IMAGE* props;
	IMAGE* subProps;
	static constexpr int ScreenWidth = 950;
	static constexpr int StartY = 50;
	static constexpr int ScreenHeight = 800;
	int ratio,subRatio, StartX = 100;
	MapCtrl* ctrl;
	void updateProp(MyMap* map, int row, int col);
	void updatePropByChange(int row, int col, int prop);

public:
	ViewMap(MyMap* map);
	~ViewMap();
	void begin();
	void printSubMap(MyMap* map,int row,int col);
	void printMap(MyMap* map);
	void quitView();
	void setCtrl(MapCtrl* ctrl);
	MapCtrl* getCtrl();
	MyMap* getMap();
	void dealChange(MyChange* change);
	void backChange(MyChange* change);
};

#endif
