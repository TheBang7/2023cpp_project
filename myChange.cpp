#include "myChange.h"

MyChange::MyChange(int all)
{
	this->all = all;
	this->col = new int[all];
	this->row = new int[all];
	this->init = new int[all];
	this->final = new int[all];
	this->initSubMap = new MyMap*[all];
	this->finalSubMap = new MyMap*[all];
	this->initFather = new MyMap*[all];
	this->finalFather = new MyMap*[all];

}

MyChange::~MyChange()
{
	delete[] this->col;
	delete[] this->row;
	delete[] this->init;
	delete[] this->final;
	delete[] this->initSubMap;
	delete[] this->finalSubMap;
	delete[] this->initFather;
	delete[] this->finalFather;
}
