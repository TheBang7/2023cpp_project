#ifndef MY_CHANGE_H
#define MY_CHANGE_H

class MyChange
{
public:
	MyChange(int all);
	int* init;
	int* final;
	int* row;
	int* col;
	int all;
	~MyChange();
};

#endif
