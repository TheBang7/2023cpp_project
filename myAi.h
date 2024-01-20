#pragma once
#include <random>
#include <string>
#include <unordered_map>

#include "myMap.h"


enum Direction
{
	up,
	down,
	left,
	right,
	ALL_Dir,
};

constexpr int ALPHA = 1;
constexpr double INI_VALUE = 10;
constexpr double EPSILON = 0.5;
constexpr double GAMMA = 0.5;
constexpr double FAIL_VALUE = -9999;
constexpr double END_VALUE = 100;


class MyAi
{
private :
	std::unordered_map<std::string, int> state_table;
	std::vector<int*> q_table;
	int getStateIndex(std::string state);
	int countState;
	int selectAction(int state_index,bool isTraining);
	std::default_random_engine randomEngine;
	int getReward(MyMap* map,std::string prev_state);

public :
	std::string stateAbstration(MyMap* map);
	MyAi();
	~MyAi();
};
