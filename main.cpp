#include "myMap.h"
#include <iostream>
#include "viewMap.h"
#include<easyx.h>
#include<graphics.h>

int main(int argc, char* argv[]) {
    std::cout << "begin" << std::endl;
    MyMap map(10, 12);
    map.printMap();
    ViewMap viewMap(&map);
    viewMap.begin();
    return 0;
}
