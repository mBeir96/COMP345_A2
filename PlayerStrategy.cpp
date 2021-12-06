#include "PlayerStrategy.h"
#include "Orders.h"
#include "Player.h"
class Orders;
class Player;



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
		issueOrder(order);
		return armies - 1;
	}
	else if (input == 2) {
		toAttack();
		return armies - 2;
	}
	else if (input == 3) {
		toDenfend();
		return armies;
	}
	else {
		cout << "Please input an correct integer from 1 to 3...\n" << endl;
	}
}

void HumanPlayerStrategy::issueOrder(string order)
{
	cout << "HumanPlayerStrategy: issueOrder() -> " << order << endl;

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
	for (auto element = player->territory.begin(); element != player->territory.end(); element++) {
		for (auto element1 = (player->getNeighbourTerritories(*element).begin()); element1 != player->getNeighbourTerritories(*(element)).end(); element1++) {
			if ((*element1)->owner != player) {
				attackList.push_back(*element1);
				(*element1)->owner->territory.erase(element1);
			}
		}
	}

	return attackList;
}

vector<Territory*> HumanPlayerStrategy::toDenfend()
{
	cout << "HumanPlayerStrategy: toDefend() " << endl;

	vector<Territory*> defendList;

	for (auto element = player->territory.begin(); element != player->territory.end(); element++) {
		defendList.push_back(*element);
	}

	return defendList;
}



AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) {
	this->player = p;
}

int AggressivePlayerStrategy::changeStrategy(string order, int armies)
{
	cout << "AggressivePlayerStrategy: changeStrategy() " << endl;

	issueOrder(order);

	toAttack();

	toDenfend();
}

void AggressivePlayerStrategy::issueOrder(string order)
{
	cout << "AggressivePlayerStrategy: issueOrder() -> " << order << " -> reinforces its strongest country. " << endl;
	int strongArmy = 0;
	Territory* strongTerritory = 0;
	for (auto element = player->territory.begin(); element != player->territory.end(); element++) {
		if ((*element)->army > strongArmy) {
			strongArmy = (*element)->army;
			strongTerritory = (*element);
		}
	}

	DeployOrders* newDeploy = new DeployOrders(player, strongTerritory, player->reinforcementPool); //will deploy onto the strongest territory
	vector<Territory*> attackList = toAttack();
	Territory* terr;

	while (strongTerritory->army > 1) {

		for (auto element = attackList.begin(); element != attackList.end(); element++) {
			terr = *element;
			AdvanceOrders* newAdvance = new AdvanceOrders(player, strongTerritory, terr , strongTerritory->army);
			player->setOrder(newAdvance);
		}
	}

	cout << "\nAggressive player deployed/Advanced all its armies and reinforcements until it no longer can." << endl;
}



vector<Territory*> AggressivePlayerStrategy::toAttack()
{
	cout << "AggressivePlayerStrategy: toAttack() " << endl;
	vector<Territory*> attackList;
	int strongArmy = 0;
	Territory* strongTerritory = 0;

	for (auto element = player->territory.begin(); element != player->territory.end(); element++) {
		if ((*element)->army > strongArmy) {
			strongArmy = (*element)->army;
			strongTerritory = (*element);
		}
	}

	for (auto element = player->getNeighbourTerritories(strongTerritory).begin(); element != player->getNeighbourTerritories(strongTerritory).end(); element++) {
		if ((*element)->owner != player) {
			attackList.push_back(*element);
		}
	}

	return attackList;
}

vector<Territory*> AggressivePlayerStrategy::toDenfend()
{
	cout << "AggressivePlayerStrategy: toDenfend() " << endl;
	cout << "Aggressive Player can not defend!" << endl;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) {
	this->player = p;
}

int BenevolentPlayerStrategy::changeStrategy(string order, int numArmy)
{
	cout << "BenevolentPlayerStrategy: changeStrategy() " << endl;
	issueOrder(order);
	toDenfend();
	
}

void BenevolentPlayerStrategy::issueOrder(string order)
{
	cout << "BenevolentPlayerStrategy: issueOrder() -> " << endl;

	vector<Territory*> defendList = toDenfend();
	while (player->getReinforcementPool() > 0) {
		for (auto element = defendList.begin(); element != defendList.end(); element++) {
			(*element)->army += 1;
			player->setReinforcementPool(player->getReinforcementPool() - 1);
		}
	}
	cout << "Benevolent player has protected its weakest territory " << endl;

}

vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
	cout << "BenevolentPlayerStrategy : never attacks" << endl;
	cout << "Benevolent Player does not attack" << endl;

}

vector<Territory*> BenevolentPlayerStrategy::toDenfend()
{
	cout << "BenevolentPlayerStrategy: toDenfend()  " << endl;

	vector<Territory*> defendList;

	Territory* begin = *player->territory.begin();
	int lowCount = begin->army;

	for (auto element = player->territory.begin(); element != player->territory.end(); element++) {
		if ((*element)->army < lowCount) {
			lowCount = (*element)->army;
		}
	}
	for (auto element = player->territory.begin(); element != player->territory.end(); element++) {
		if ((*element)->army== lowCount) {
			defendList.push_back(*element);
		}
	}

	return defendList;
}


#pragma region Neutral Player Strategy


int NeutralPlayerStrategey::changeStrategy(string, int)
{
	return 0;
}

void NeutralPlayerStrategey::issueOrder(string)
{
}

vector<Territory*> NeutralPlayerStrategey::toAttack()
{
}

vector<Territory*> NeutralPlayerStrategey::toDenfend()
{
}

#pragma endregion

#pragma region Cheater Player Strategy

int CheaterPlayerStrategey::changeStrategy(string, int)
{
	return 0;
}

void CheaterPlayerStrategey::issueOrder(string)
{
}

vector<Territory*> CheaterPlayerStrategey::toAttack()
{
}

vector<Territory*> CheaterPlayerStrategey::toDenfend()
{
}

#pragma endregion