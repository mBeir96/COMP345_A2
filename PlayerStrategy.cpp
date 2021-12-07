#include "PlayerStrategy.h"
#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include <vector>;
using namespace std;
class Orders;
class Player;
class Territory;

#pragma region Human Player Strategy

HumanPlayerStrategy::HumanPlayerStrategy(Player* p) {
	this->player = p;

}

int HumanPlayerStrategy::changeStrategy(string order, int armies)
{
	cout << "HumanPlayerStrategy: Please choose a strategy from the following \n"
		"1 for issueOrder(), 2 for toAttack(), 3 for toDefend(). " << endl;
	int input;
	cin >> input;
	if (input == 1) {
		issueOrder();
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

void HumanPlayerStrategy::issueOrder()
{
	int input = 0;

	cout << "Which order are you issuing?" << endl;
	cout << "1. Deploy" << endl;
	cout << "2. Advance" << endl;
	cout << "3. Airlift" << endl;
	cout << "4. Bomb" << endl;
	cout << "5. Blockade" << endl;
	cout << "6. Negotiate" << endl;

	//fix problem with orders
	cin >> input;
	switch (input) {
	case (1): {
		DeployOrders* order1 = new DeployOrders();
		cout << "player will" << order1 << endl;
		player->setOrder(order1);
	}
	case (2): {
		AdvanceOrders* order1 = new AdvanceOrders();
		cout << "player will" << order1<< endl;
		player->setOrder(order1);
	}
	case (3): {
		BombOrders* order1 = new BombOrders();
		cout << "player will" << order1 << endl;
		player->setOrder(order1);
	}
	case (4): {
		BlockadeOrders* order1 = new BlockadeOrders();
		cout << "player will" << order1<< endl;
		player->setOrder(order1);
	}
	case (5): {
		AirliftOrders* order1 = new AirliftOrders();
		cout << "player will" << order1 << endl;
		player->setOrder(order1);
	}
	case (6): {
		NegotiateOrders* order1 = new NegotiateOrders();
		cout << "player will" << order1<< endl;
		player->setOrder(order1);
	}
	default: {
		cout << "Please Enter a valid order number!" << endl;
	}
	}

}

vector<Territory*> HumanPlayerStrategy::toAttack()
{
	cout << "HumanPlayerStrategy: toAttack() " << endl;
	vector<Territory*> attackList;
	/*for (auto element = player->getTerritory().begin(); element != player->getTerritory().end(); element++) {
		for (auto element1 = (player->getNeighbourTerritories(*element).begin()); element1 != player->getNeighbourTerritories(*(element)).end(); element1++) {
			if ((*element1)->getTerritoryOwner() != player) {
				attackList.push_back(*element1);
				(*element1)->getTerritoryOwner()->getTerritory().erase(element1);
			}
		}
	}
	*/
	return attackList;
}

vector<Territory*> HumanPlayerStrategy::toDefend()
{
	cout << "HumanPlayerStrategy: toDefend() " << endl;

	vector<Territory*> defendList;

	for (auto element = player->getTerritory().begin(); element != player->getTerritory().end(); element++) {
		defendList.push_back(*element);
	}

	return defendList;
}

void HumanPlayerStrategy::PrintStrategy()
{
	std::cout << "Human Player Strategy\n";
}

#pragma endregion

#pragma region Aggressive Player Strategy

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) {
	this->player = p;
}

int AggressivePlayerStrategy::changeStrategy(string order, int armies)
{
	cout << "AggressivePlayerStrategy: changeStrategy() " << endl;

	issueOrder();

	toAttack();

	toDefend();

	return 0;
}

void AggressivePlayerStrategy::issueOrder()
{
	int strongArmy = 0;
	Territory* strongTerritory = 0;
	for (int i = 0; i < player->getTerritory().size(); i++) {
		if (player->getTerritory().at(i)->getArmyAmount() >= strongArmy) {
			strongArmy = player->getTerritory().at(i)->getArmyAmount();
			strongTerritory = player->getTerritory().at(i);
		}
	}

	DeployOrders* newDeploy = new DeployOrders(player, strongTerritory, player->getReinforcementPool()); //will deploy onto the strongest territory
	player->setOrder(newDeploy);
	vector<Territory*> attackList = toAttack();
	Territory* terr;

	while (strongTerritory->army >= 1) {

		for (int i = 0; i < attackList.size() && strongTerritory->army >= 1; i++) {
			terr = attackList.at(i);
			AdvanceOrders* newAdvance = new AdvanceOrders();
			newAdvance->setSelfPlayers(player);
			newAdvance->setArmyUnits(1);
			newAdvance->setSourceTerritory(strongTerritory);
			newAdvance->setTargetTerritory(terr);
			player->setOrder(newAdvance);
			strongTerritory->setArmyAmount(strongTerritory->getArmyAmount() - 1);
		}
	}

	//cout << "\nAggressive player deployed/Advanced all its armies and reinforcements until it no longer can." << endl;
}

vector<Territory*> AggressivePlayerStrategy::toAttack()
{
	vector<Territory*> attackList;
	int strongArmy = 0;
	Territory* strongTerritory = new Territory();

	for (int i = 0; i < player->getTerritory().size(); i++) {
		if (player->getTerritory().at(i)->getArmyAmount() > strongArmy) {
			strongArmy = player->getTerritory().at(i)->getArmyAmount();
			strongTerritory = player->getTerritory().at(i);
		}
	}

	for (int i = 0; i < strongTerritory->edges.size(); i++) {
		if (strongTerritory->edges.at(i)->getTerritoryOwner() != player) {
			attackList.push_back(strongTerritory->edges.at(i));
		}
	}

	return attackList;
}

vector<Territory*> AggressivePlayerStrategy::toDefend()
{
	vector<Territory*> DefendList;
	return DefendList;
	cout << "AggressivePlayerStrategy: toDenfend() " << endl;
	cout << "Aggressive Player can not defend!" << endl;
}

void AggressivePlayerStrategy::PrintStrategy()
{
	std::cout << "Aggressive Player Strategy\n";
}

#pragma endregion

#pragma region Benevolent Player Strategy

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) {
	this->player = p;
}

int BenevolentPlayerStrategy::changeStrategy(string order, int numArmy)
{
	cout << "BenevolentPlayerStrategy: changeStrategy() " << endl;
	issueOrder();
	toDefend();

	return 0;
	
}

void BenevolentPlayerStrategy::issueOrder()
{

	vector<Territory*> defendList = toDefend();
	DeployOrders* o;
	while (player->getReinforcementPool() > 0) {
		for (int i = 0; i < defendList.size(); i++) {
			o = new DeployOrders();
			o->setSelfPlayers(player);
			o->setNumArmy(1);
			o->setTargetTerritory(defendList.at(i));
			player->setOrder(o);
			player->setReinforcementPool(player->getReinforcementPool() - 1);
		}
	}

}

vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
	vector<Territory*> AttackList;
	return AttackList;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
	vector<Territory*> defendList;
	Territory* begin = *player->territory.begin();
	int lowCount = begin->army;

	for (int i = 0; i < player->getTerritory().size(); i++) {
		if (player->getTerritory().at(i)->getArmyAmount() < lowCount) {
			lowCount = player->getTerritory().at(i)->getArmyAmount();
		}
	}
	for (int i = 0; i < player->getTerritory().size(); i++) {
		
		if (player->getTerritory().at(i)->getArmyAmount() == lowCount) {
			defendList.push_back(player->getTerritory().at(i));
		}
	}

	return defendList;
}

void BenevolentPlayerStrategy::PrintStrategy()
{
	std::cout << "Benevolent Player Strategy\n";
}

#pragma endregion

#pragma region Neutral Player Strategy

//sets player
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {
	this->player = player;
	int terrCount = 0;
	int armyAmount = 0;
	for (int i = 0; i < player->getTerritory().size(); i++)
	{
		terrCount += 1;
		armyAmount += player->getTerritory().at(i)->army;
	}

	territoryCount = terrCount;
	armyCount = armyAmount;
}

int NeutralPlayerStrategy::changeStrategy(string, int)
{
	return 0;
}

void NeutralPlayerStrategy::issueOrder()
{
	int territoryAmount = 0;
	int armyAmount = 0;
	for (int i = 0; i < player->getTerritory().size(); i++)
	{
		territoryAmount += 1;
		armyAmount += player->getTerritory().at(i)->army;
	}

	//if army is attacked
	if (territoryAmount < territoryCount || armyAmount < armyCount) {
		
		//change player strategy
		player->setPlayerStrategy(Aggressive);
		player->issueOrder();

		//not sure if this is allowed, remove if necessary
		this->~NeutralPlayerStrategy();
	}
	else {
		territoryCount = territoryAmount;
		armyCount = armyAmount;
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

void NeutralPlayerStrategy::PrintStrategy()
{
	std::cout << "Neutral Player Strategy\n";
}

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{

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
void CheaterPlayerStrategy::issueOrder()
{
	player->territory.at(0);
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
		for (int j = 0; j < territory.at(i)->edges.size(); j++)
		{
			if (territory.at(i)->edges.at(j)->getTerritoryOwner() != player)
			{
				AttackList.push_back(territory.at(i)->edges.at(j));
			}
		}
	}
	return AttackList;
}

//cheater never needs to defend
vector<Territory*> CheaterPlayerStrategy::toDefend()
{
	vector<Territory*> DefendList;
	return DefendList;
}

void CheaterPlayerStrategy::PrintStrategy()
{
	std::cout << "Cheater Player Strategy\n";
}

#pragma endregion
