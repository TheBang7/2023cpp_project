#include "myAi.h"

#include "myAi.h"

MyAi::MyAi() : randomEngine(std::random_device()())
{
	countState = 0;
}

MyAi::~MyAi()
{
	q_table.clear();
}

double MyAi::getReward(MyMap* map, std::string& prev_state, std::string& state, bool isInitMap)
{
	if (isInitMap && map->checkMap())
	{
		return END_VALUE;
	}
	else if (state == prev_state)
	{
		return FAIL_VALUE;
	}
	else
	{
		int count = 0;
		for (int i = 0; i < map->getNumRows(); i++)
			for (int j = 1; j < map->getNumCols(); j++)
			{
				if ((map->getElementType(i, j) == Prop::HIT ||
						map->getElementType(i, j) == Prop::SUB_MAP) &&
					map->getElementRemainsType(i, j) == Prop::BOX_DEST ||
					map->getElementType(i, j) == Prop::MAN_HIT)
					count++;
				else if (map->getElementType(i, j) == Prop::SUB_MAP && map->getSubMap(i, j)->checkMap())count++;
			}
		return count * FULL_VALUE;
	}
}

double MyAi::updateQ_table(int state_index, int prev_state_index, int action, double reward)
{
	double q_predict = q_table[prev_state_index][action];
	double maxV = 0;
	for (int i = 0; i < 4; i++)
	{
		if (q_table[state_index][i] > maxV)maxV = q_table[state_index][i];
	}
	double q_target = reward + GAMMA * maxV;
	if (reward > 0)
	{
	}
	q_table[prev_state_index][action] = q_predict + ALPHA * (q_target - q_predict);
	double back = (reward - FAIL_VALUE) <= 1 ? 0 : ALPHA * abs((q_target - q_predict));
	return back > 0 ? back : -back;
}


int MyAi::selectAction(int state_index, bool isTraining, int action)
{
	int selAction;
	std::uniform_real_distribution<double> distribution(0, 1);
	double t = distribution(randomEngine);
	if (isTraining && t > EPSILON)
	{
		std::uniform_int_distribution<int> dis(0, Direction::ALL_Dir - 1);
		selAction = dis(randomEngine);
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
		selAction = direction;
	}

	return selAction;
}


int MyAi::getStateIndex(std::string state)
{
	auto iter = state_table.find(state);
	if (iter == state_table.end())
	{
		std::vector<double> values(Direction::ALL_Dir, INI_VALUE);
		q_table.push_back(values);
		state_table.emplace(state, countState);
		return countState++;
	}
	else
	{
		return iter->second;
	}
}


std::string MyAi::stateAbstration(MyMap* map)
{
	std::string s;
	s.append(map->getMapName());
	s.append("-").append(std::to_string(map->getManPositionRow())).append("_").append(
		std::to_string(map->getManPositionCol()));
	int row = map->getNumRows();
	int col = map->getNumCols();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (map->getElementType(i, j) == Prop::BOX)
			{
				std::string ii = std::to_string(i);
				std::string jj = std::to_string(j);
				s.append("-").append(ii).append("_").append(jj);
			}
			else if (map->getElementType(i, j) == Prop::SUB_MAP)
			{
				std::string ii = std::to_string(i);
				std::string jj = std::to_string(j);
				s.append("-").append(map->getSubMap(i, j)->getMapName())
				 .append("_").append(ii).append("_").append(jj);
			}
		}
	}
	return s;
}
