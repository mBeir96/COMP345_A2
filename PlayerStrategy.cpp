#include "PlayerStrategy.h"
#include <vector>;
using namespace std;


int HumanPlayerStrategy::changeStrategy(string order, int armies)
{
	cout << "HumanPlayerStrategy: Please choose a strategy from the following \n"
		"1 for issueOrder(), 2 for toAttack(), 3 for toDefend(). " << endl;
	int input;
	cin >> input;
	if (input == 1) {
		issueOrder(order);
		return armies - 1;
	}
	else if (input == 2) {
		toAttack();
		return armies - 2;
	}
	else if (input == 3) {
		toDefend();
		return armies;
	}
	else {
		cout << "Please input an correct integer from 1 to 3...\n" << endl;
	}
}

void HumanPlayerStrategy::issueOrder(string order)
{
	cout << "HumanPlayerStrategy: issueOrder() -> " << order << endl;
}

vector<Territory*> HumanPlayerStrategy::toAttack()
{
	vector<Territory*> DefendList;
	return DefendList;
	cout << "HumanPlayerStrategy: toAttack() " << endl;
}

vector<Territory*> HumanPlayerStrategy::toDefend()
{
	vector<Territory*> DefendList;
	return DefendList;
	cout << "HumanPlayerStrategy: toAttack() " << endl;
	vector<Territory*> t;
	//return t;
}

int AggressivePlayerStrategy::changeStrategy(string order, int armies)
{
	cout << "AggressivePlayerStrategy: makeDecision() " << endl;
	
	issueOrder(order);
	
	toAttack();

	toDefend();
	return armies - 5;
}

void AggressivePlayerStrategy::issueOrder(string order)
{
	cout << "AggressivePlayerStrategy: issueOrder() -> " << order << " -> reinforces its strongest country. " << endl;
}

vector<Territory*> AggressivePlayerStrategy::toAttack()
{
	vector<Territory*> DefendList;
	return DefendList;
	cout << "AggressivePlayerStrategy: toAttack() " << endl;
}

vector<Territory*> AggressivePlayerStrategy::toDefend()
{
	vector<Territory*> DefendList;
	return DefendList;
	cout << "AggressivePlayerStrategy: toDenfend() -> maximize aggregation of forces in the country" << endl;
}

int BenevolentPlayerStrategy::changeStrategy(string order, int numArmy)
{
	cout << "BenevolentPlayerStrategy: makeDecision() " << endl;
	//focus on protecting its weak country
	issueOrder(order);
	//never attacks, toDefend
	toDefend();
	return numArmy - 1;
}

void BenevolentPlayerStrategy::issueOrder(string order)
{
	cout << "BenevolentPlayerStrategy: issueOrder() -> " << order << " -> reinforces its weakest country. " << endl;
}

vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
	vector<Territory*> DefendList;
	return DefendList;
	cout << "BenevolentPlayerStrategy : never attacks" << endl;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
	
	vector<Territory*> DefendList;
	return DefendList; 
	cout << "BenevolentPlayerStrategy: toDenfend() -> move armies to weaker countries. " << endl;
}


#pragma region Neutral Player Strategy

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {
	this->player = player;
}

int NeutralPlayerStrategy::changeStrategy(string, int)
{
	return 0;
}

void NeutralPlayerStrategy::issueOrder(string)
{
}

vector<Territory*> NeutralPlayerStrategy::toAttack()
{
	vector<Territory*> DefendList;
	return DefendList;
}

vector<Territory*> NeutralPlayerStrategy::toDefend()
{
	vector<Territory*> DefendList;
	return DefendList;
}

#pragma endregion

#pragma region Cheater Player Strategy

CheaterPlayerStrategey::CheaterPlayerStrategey(Player* player)
{
	this->player = player;
}

int CheaterPlayerStrategey::changeStrategy(string, int)
{
	return 0;
}

void CheaterPlayerStrategey::issueOrder(string)
{
}

vector<Territory*> CheaterPlayerStrategey::toAttack()
{
	vector<Territory*> AttackList;
	vector<Territory*> territory = player->getTerritory();

	for (int i = 0; i < territory.size(); i++)
	{
		string temp = player->getName();
		if (!temp.compare(territory[i]->getTerritoryOwner()->getName()) == 0)
			AttackList.push_back(territory[i]);

	}
	return AttackList;
}

vector<Territory*> CheaterPlayerStrategey::toDefend()
{
	vector<Territory*> DefendList;
	return DefendList;
}

#pragma endregion
