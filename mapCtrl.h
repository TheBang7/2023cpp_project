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
    static constexpr char key_left = 'l';
    static constexpr char key_right = 'r';
    ViewMap* viewMap;
};

#endif // MAP_CTRL_H
