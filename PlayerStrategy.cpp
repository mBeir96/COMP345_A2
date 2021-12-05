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

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player)
{
	this->player = player;
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

//sets player
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {
	this->player = player;
	for (int i = 0; i < player->getTerritory().size(); i++)
	{
		*territoryCount += 1;
		*armyCount += player->getTerritory().at(i)->army;
	}
}

int NeutralPlayerStrategy::changeStrategy(string, int)
{
	return 0;
}

void NeutralPlayerStrategy::issueOrder(string)
{
	int territoryAmount = 0;
	int armyAmount = 0;
	for (int i = 0; i < player->getTerritory().size(); i++)
	{
		territoryAmount += 1;
		armyAmount += player->getTerritory().at(i)->army;
	}

	//if army is attacked
	if (territoryAmount != *territoryCount || armyAmount != *armyCount) {
		
		//change player strategy
		player->setPlayerStrategy(Aggressive);
		player->issueOrder();

		//not sure if this is allowed, remove if necessary
		this->~NeutralPlayerStrategy();
	}
}

//never needs to attack
vector<Territory*> NeutralPlayerStrategy::toAttack()
{
	vector<Territory*> DefendList;
	return DefendList;
}

//never needs to defend
vector<Territory*> NeutralPlayerStrategy::toDefend()
{
	vector<Territory*> DefendList;
	return DefendList;
}

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
	delete(territoryCount);
	delete(armyCount);
}

#pragma endregion

#pragma region Cheater Player Strategy

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player)
{
	this->player = player;
}

int CheaterPlayerStrategy::changeStrategy(string, int)
{
	return 0;
}

//takes all adjacent territory
void CheaterPlayerStrategy::issueOrder(string)
{
	vector<Territory*> AttackList = this->toAttack();
	Territory* terr;
	for (int i = 0; i < AttackList.size(); i++)
	{
		
		terr = AttackList.at(i);
		int index = 0;
		for (int i = 0; i < terr->player->getTerritory().size(); i++)
		{
			if (terr == terr->player->getTerritory().at(i))
			{
				index = i;
				break;
			}
		}

		//remove territory from enemy player
		terr->player->removeTerritory(index);
		//change ownership
		terr->setTerritoryOwner(player);
		//give cheater ownership
		terr->setArmyAmount(0);
		player->setTerritory(terr);
	}
}

vector<Territory*> CheaterPlayerStrategy::toAttack()
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

//cheater never needs to defend
vector<Territory*> CheaterPlayerStrategy::toDefend()
{
	vector<Territory*> DefendList;
	return DefendList;
}

#pragma endregion
