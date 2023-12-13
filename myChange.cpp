#include "myChange.h"

MyChange::MyChange(int all)
{
	this->all = all;
	this->col = new int[all];
	this->row = new int[all];
	this->init = new int[all];
	this->final = new int[all];
}

MyChange::~MyChange()
{
	delete[] this->col;
	delete[] this->row;
	delete[] this->init;
	delete[] this->final;
}
