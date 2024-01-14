
#ifndef MY_CHANGE_H
#define MY_CHANGE_H
#include "myMap.h"
class MyMap;
class MyChange
{
public:
	MyChange(int all);
	int* init;
	int* final;
	int* row;
	int* col;
	int all;
	MyMap** initSubMap;
	MyMap** finalSubMap;
	MyMap** initFather;
	MyMap** finalFather;
	MyMap* initView;
	MyMap* finalView;
	~MyChange();
};

#endif
