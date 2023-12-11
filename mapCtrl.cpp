#include "mapCtrl.h"
#include "MyMap.h"
#include "viewMap.h"

MapCtrl::MapCtrl(ViewMap* viewMap)
{
	this->viewMap = viewMap;
	viewMap->setCtrl(this);
}

void MapCtrl::begin()
{
}
