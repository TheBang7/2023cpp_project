#include "MyMap.h"
#include "viewMap.h"
#include <iostream>
#include<easyx.h>
#include<graphics.h>

ViewMap::ViewMap(MyMap* map)
{
	this->map = map;
	props = new IMAGE[Prop::ALL];
	ratio = (ScreenHeight - 2 * StartY) / max(map->getNumCols(), map->getNumCols());
	StartX = (ScreenWidth - ratio * max(map->getNumCols(), map->getNumCols())) / 2;
	init_picture();
}

void ViewMap::init_picture()
{
	loadimage(&(this->background), "resource/background.bmp", ScreenWidth, ScreenHeight, true);
	loadimage(&(props[Prop::BOX]), "resource/box.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::FLOOR]), "resource/floor.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::BOX_DEST]), "resource/des.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::WALL]), "resource/wall.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::MAN]), "resource/man.bmp", this->ratio, this->ratio, true);
}

void ViewMap::begin()
{
	initgraph(ScreenWidth, ScreenHeight);
	putimage(0, 0, &this->background);
	for (int i = 0; i < this->map->getNumRows(); i++)
	{
		for (int j = 0; j < this->map->getNumCols(); j++)
		{
			putimage(StartX + j * ratio, StartY + i * ratio, &this->props[map->getElement(i, j)]);
		}
	}
}


void ViewMap::quitView()
{
}


void ViewMap::setCtrl(MapCtrl* ctrl)
{
	this->ctrl = ctrl;
}

MapCtrl* ViewMap::getCtrl()
{
	return this->ctrl;
}

ViewMap::~ViewMap()
{
	delete[] props;
}
