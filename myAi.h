#pragma once
#include <random>
#include <string>
#include <unordered_map>
#include <sstream>

#include "myMap.h"


enum Direction
{
	up,
	down,
	left,
	right,
	ALL_Dir,
};

constexpr double ALPHA = 1;
constexpr double INI_VALUE = 0;
constexpr double FULL_VALUE = 5;
constexpr double EPSILON = 0.5;
constexpr double GAMMA = 0.9;
constexpr double FAIL_VALUE = -9999;
constexpr double END_VALUE = 999999;


class MyAi
{
private:
	std::unordered_map<std::string, int> state_table;
	int countState;
	std::default_random_engine randomEngine;


public :
	std::string stateAbstration(MyMap* map);
	std::vector<std::vector<double>> q_table;
	int selectAction(int state_index, bool isTraining,int action);
	int getStateIndex(std::string state);
	double updateQ_table(int state_index, int prev_state_index, int action, double reward);
	double getReward(MyMap* map, std::string &prev_state, std::string &state£¬bool,bool isInitMap);
	MyAi();
	~MyAi();
};
