#include "myAi.h"

MyAi::MyAi() : randomEngine(std::random_device()())
{
	countState = 0;
}

MyAi::~MyAi()
{
	for (int* ptr : q_table)
	{
		delete ptr;
	}
	q_table.clear();
}

int MyAi::getReward(MyMap* map,std::string prev_state)
{
	if (map->checkMap())
	{
		return END_VALUE;
	}else
	{
	}
}


int MyAi::selectAction(int state_index, bool isTraining)
{
	std::uniform_real_distribution<double> distribution(0, 1);
	if (isTraining && distribution(randomEngine) > EPSILON)
	{
		std::uniform_int_distribution<int> dis(0, Direction::ALL_Dir - 1);
		return dis(randomEngine);
	}
	else
	{
		int direction = 0;
		double max_value = q_table[state_index][0];
		for (int i = 1; i < Direction::ALL_Dir; i++)
		{
			if (q_table[state_index][i] > max_value)
			{
				direction = i;
				max_value = q_table[state_index][i];
			}
		}
		return direction;
	}
}


int MyAi::getStateIndex(std::string state)
{
	auto pair = state_table.find(state);
	if (pair == state_table.end())
	{
		int* values = new int(Direction::ALL_Dir);
		for (int i = 0; i < Direction::ALL_Dir; i++)
		{
			values[i] = INI_VALUE;
		}
		q_table.push_back(values);
		state_table.insert(std::make_pair(state, countState++));
		return countState - 1;
	}
	else return pair->second;
}


std::string MyAi::stateAbstration(MyMap* map)
{
	std::string s = map->getMapName() + "-" + std::to_string(map->getManPositionRow()) + "_" +
		std::to_string(map->getManPositionCol());
	int row = map->getNumRows();
	int col = map->getNumCols();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (map->getElementType(i, j) == Prop::BOX)
			{
				s += "-" + std::to_string(i) + "_" + std::to_string(j);
			}
			else if (map->getElementType(i, j) == Prop::SUB_MAP)
			{
				s += "-" + map->getSubMap(i, j)->getMapName()
					+ "_" + std::to_string(i) + "_" + std::to_string(j);
			}
		}
	}
	return s;
}
