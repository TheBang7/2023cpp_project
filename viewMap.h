//viewMap.h
#ifndef VIEW_MAP_H
#define VIEW_MAP_H
#include <graphics.h>

#include "mapCtrl.h"
#include "myMap.h"


class ViewMap
{
private:
	void init_picture();
	MyMap* map;
	IMAGE background;
	IMAGE* props;
	static constexpr int ScreenWidth = 950;
	static constexpr int StartY = 50;
	static constexpr int ScreenHeight = 800;
	int ratio, StartX = 100;
	MapCtrl* ctrl;
	void updateProp(int row, int col);
	void updatePropByChange(int row, int col, int prop);

public:
	ViewMap(MyMap* map);
	~ViewMap();
	void begin();
	void quitView();
	void setCtrl(MapCtrl* ctrl);
	MapCtrl* getCtrl();
	MyMap* getMap();
	void dealChange(Change change);
	void backChange(Change change);
};

#endif
