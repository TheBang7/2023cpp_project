#include "MyMap.h"
#include "viewMap.h"
#include <iostream>
#include<easyx.h>
#include<graphics.h>

ViewMap::ViewMap(MyMap* map)
{
	this->map = map;
	props = new IMAGE[Prop::ALL];
	subProps = new IMAGE[Prop::ALL];
	initgraph(ScreenWidth, ScreenHeight);
}

void ViewMap::init_picture()
{
	loadimage(&(this->background), "resource/background.bmp", ScreenWidth, ScreenHeight, true);
	loadimage(&(props[Prop::BOX]), "resource/box.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::FLOOR]), "resource/floor.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::BOX_DEST]), "resource/des.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::WALL]), "resource/wall.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::MAN]), "resource/man.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::HIT]), "resource/box_hit.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::MAN_DEST]), "resource/player_des.bmp", this->ratio, this->ratio, true);
	loadimage(&(props[Prop::MAN_HIT]), "resource/player_hit.bmp", this->ratio, this->ratio, true);
}

void ViewMap::loadSubMapPicture(MyMap* subMap)
{
	subRatio = ratio / max(subMap->getNumCols(), subMap->getNumCols());
	loadimage(&(this->subBackground), "resource/background.bmp", ratio, ratio, true);
	loadimage(&(subProps[Prop::BOX]), "resource/box.bmp", this->subRatio, this->subRatio, true);
	loadimage(&(subProps[Prop::FLOOR]), "resource/floor.bmp", this->subRatio, this->subRatio, true);
	loadimage(&(subProps[Prop::BOX_DEST]), "resource/des.bmp", this->subRatio, this->subRatio, true);
	loadimage(&(subProps[Prop::WALL]), "resource/wall.bmp", this->subRatio, this->subRatio, true);
	loadimage(&(subProps[Prop::MAN]), "resource/man.bmp", this->subRatio, this->subRatio, true);
	loadimage(&(subProps[Prop::HIT]), "resource/box_hit.bmp", this->subRatio, this->subRatio, true);
	loadimage(&(subProps[Prop::MAN_DEST]), "resource/player_des.bmp", this->subRatio, this->subRatio, true);
	loadimage(&(subProps[Prop::MAN_HIT]), "resource/player_hit.bmp", this->subRatio, this->subRatio, true);
}

void ViewMap::begin()
{
	ratio = (ScreenHeight - 2 * StartY) / max(map->getNumCols(), map->getNumCols());
	subRatio = ratio / max(map->getNumCols(), map->getNumCols());
	StartX = (ScreenWidth - ratio * max(map->getNumCols(), map->getNumCols())) / 2;
	init_picture();
	putimage(0, 0, &this->background);
	this->printMap(this->getMap());
}

void ViewMap::printMap(MyMap* map)
{
	putimage(0, 0, &this->background);
	for (int i = 0; i < map->getNumRows(); i++)
	{
		for (int j = 0; j < map->getNumCols(); j++)
		{
			updateProp(map, i, j);
		}
	}
}


void ViewMap::printSubMap(MyMap* subMap, int row, int col)
{
	loadSubMapPicture(subMap);
	putimage(StartX + col * ratio, StartY + row * ratio, &this->subBackground);
	for (int i = 0; i < subMap->getNumRows(); i++)
	{
		for (int j = 0; j < subMap->getNumCols(); j++)
		{
			if (subMap->getElementType(i, j) != Prop::SUB_MAP)
				putimage(StartX + col * ratio + j * subRatio, StartY + row * ratio + i * subRatio,
				         &this->subProps[subMap->getElementType(i, j)]);
			else
				putimage(StartX + col * ratio + j * subRatio, StartY + row * ratio + i * subRatio,
				         &this->subProps[Prop::BOX]);
		}
	}
}

void ViewMap::updateProp(MyMap* map, int row, int col)
{
	if (map->getElementType(row, col) != Prop::SUB_MAP)
		putimage(StartX + col * ratio, StartY + row * ratio, &this->props[map->getElementType(row, col)]);
	else printSubMap(map->getSubMap(row, col), row, col);
}

void ViewMap::updatePropByChange(int row, int col, int prop)
{
	putimage(StartX + col * ratio, StartY + row * ratio, &this->props[prop]);
}


void ViewMap::quitView()
{
}


MyMap* ViewMap::getMap()
{
	return this->map;
}

ViewMap::~ViewMap()
{
	delete[] props;
	delete[]subProps;
}

void ViewMap::dealChange(MyChange* change)
{
	for (int i = 0; i < change->all; i++)
	{
		if (change->final[i] != Prop::SUB_MAP)
			updatePropByChange(change->row[i], change->col[i], change->final[i]);
		else
			printSubMap(change->finalSubMap[i], change->row[i], change->col[i]);
	}
	if (map->outsideMap == map)
	{
		printSubMap(map, map->outsidePosition.row, map->outsidePosition.col);
	}
}

void ViewMap::backChange(MyChange* change)
{
	for (int i = 0; i < change->all; i++)
	{
		if (change->init[i] != Prop::SUB_MAP)
			updatePropByChange(change->row[i], change->col[i], change->init[i]);
		else
			printSubMap(change->initSubMap[i], change->row[i], change->col[i]);
	}
	if (map->outsideMap == map)
	{
		printSubMap(map, map->outsidePosition.row, map->outsidePosition.col);
	}
}

void ViewMap::setMap(MyMap* map)
{
	this->map = map;
}
