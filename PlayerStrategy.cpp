#include "PlayerStrategy.h"
#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include <vector>;
#include <set>;
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
	const int EXITNUMBER = 7;
	int input = 0;

	while (input != EXITNUMBER) {
		cout << "Which order are you issuing?" << endl;
		cout << "1. Deploy" << endl;
		cout << "2. Advance" << endl;
		cout << "3. Airlift" << endl;
		cout << "4. Bomb" << endl;
		cout << "5. Blockade" << endl;
		cout << "6. Negotiate" << endl;
		cout << EXITNUMBER << ". Exit" << endl;

		//fix problem with orders
		cin >> input;
		switch (input) {
		case (1): 
			Deploy();
			break;
		case (2): 
			Advance();
			break;
		case (3): 
			Airlift();
			break;
		case (4): 
			Bomb();
			break;
		case (5): 
			Blockade();
			break;
		case (6): 
			Negotiate();
			break;
		case (EXITNUMBER): 
			cout << "Exiting" << endl;
			break;
		default: 
			cout << "Please Enter a valid order number!" << endl;
			break;
		}
	}
}

vector<Territory*> HumanPlayerStrategy::toAttack()
{
	cout << "HumanPlayerStrategy: toAttack() " << endl;
	vector<Territory*> attackList;
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

#pragma region Helper Functions

void HumanPlayerStrategy::Deploy()
{

	//show necessary information
	ShowTerritory();
	cout << "Available Reinforcement: " << player->getReinforcementPool() << endl;

	//get region and reinforcement
	int region = ChooseValidOption(player->getTerritory().size());
	int rein = GetArmyNumber(player->getReinforcementPool());
	player->setReinforcementPool(player->getReinforcementPool() - rein);

	//make order
	DeployOrders* deployOrder = new DeployOrders();
	deployOrder->setSelfPlayers(player);
	deployOrder->setTargetTerritory(player->getTerritory().at(region));
	deployOrder->setNumArmy(rein);

	player->setOrder(deployOrder);
}

void HumanPlayerStrategy::Advance()
{
	//get source territory
	ShowTerritory();
	int source = ChooseValidOption(player->getTerritory().size());
	
	//get target territory
	cout << "These are the target Territories" << endl;
	for (int i = 0; i < player->getTerritory().at(source)->edges.size(); i++)
	{
		cout << i << ". " << player->getTerritory().at(source)->edges.at(i)->getTname() << " (" << player->getTerritory().at(source)->edges.at(i)->getArmyAmount() << ")";
		if (player->getTerritory().at(source)->edges.at(i)->getTerritoryOwner() != player)
		{
			cout << " (enemy)";
		}
		cout << endl;
	}
	int target = ChooseValidOption(player->getTerritory().size());

	//get army amount
	cout << "Source armount is " << player->getTerritory().at(source)->getArmyAmount() << endl;
	int army = GetArmyNumber(player->getTerritory().at(source)->getArmyAmount());

	//make advance orders
	AdvanceOrders* advanceOrder = new AdvanceOrders();
	advanceOrder->setSelfPlayers(player);
	advanceOrder->setSourceTerritory(player->getTerritory().at(source));
	advanceOrder->setTargetTerritory(player->getTerritory().at(source)->edges.at(target));
	advanceOrder->setArmyUnits(army);

	player->setOrder(advanceOrder);
}

void HumanPlayerStrategy::Airlift()
{
	ShowTerritory();

	int source = ChooseValidOption(player->getTerritory().size());
	
	cout << "Choose another region to Airlift towards" <<endl;
	int target = ChooseValidOption(player->getTerritory().size());

	cout << "Choose army amount to source" << endl;
	cout << "Available army: " << player->getTerritory().at(source)->getArmyAmount() << endl;
	int army = GetArmyNumber(player->getTerritory().at(source)->getArmyAmount());

	AirliftOrders* airliftOrder = new AirliftOrders();
	airliftOrder->setSelfPlayers(player);
	airliftOrder->setSourceTerritory(player->getTerritory().at(source));
	airliftOrder->setTargetTerritory(player->getTerritory().at(target));
	airliftOrder->setNumArmy(army);

	player->setOrder(airliftOrder);
}

void HumanPlayerStrategy::Bomb()
{
	//get enemy territory
	vector<Territory*> enemyTerritory = GetEnemyTerritory();

	//choose enemy territory
	cout << "These are enemy Territory Territories" << endl;
	for (int i = 0; i < enemyTerritory.size(); i++)
	{
		cout << i << ". " << enemyTerritory.at(i)->getTname() << " (" << enemyTerritory.at(i)->getArmyAmount() << ")";
		cout << endl;
	}
	int territory = ChooseValidOption(enemyTerritory.size());

	//make bomb orders
	BombOrders* bombOrders = new BombOrders();
	bombOrders->setSelfPlayers(player);
	bombOrders->setTargetTerritory(enemyTerritory.at(territory));

	player->setOrder(bombOrders);
}

void HumanPlayerStrategy::Blockade()
{
}

void HumanPlayerStrategy::Negotiate()
{
	set<Player*> playersTemp = GetPlayers();
	vector<Player*> players = vector<Player*>(playersTemp.begin(), playersTemp.end());

	cout << "These are the valid player options" << endl;
	for (int i = 0; i < players.size(); i++)
	{
		next(players.begin(), i);
		cout << i << ". " << players.at(i)->getName() << endl;
	}

	int chosenPlayer = ChooseValidOption(players.size());

	NegotiateOrders* negotiateOrders = new NegotiateOrders();
	negotiateOrders->setSelfPlayers(player);
	negotiateOrders->setPeacePlayer(players.at(chosenPlayer));

	player->setOrder(negotiateOrders);
}

int HumanPlayerStrategy::ChooseValidOption(int max)
{
	int region = -1;
	while (region >= max || region < 0) {
		cout << "choose a valid option: ";
		cin >> region;
	}

	return region;
}

int HumanPlayerStrategy::GetArmyNumber(int army)
{
	int rein = -1;
	while (rein > army || rein < 0) {
		cout << "choose a valid amount: ";
		cin >> rein;
		cout << endl;
	}

	return rein;
}

void HumanPlayerStrategy::ShowTerritory()
{
	cout << "These are the available to Choose from" << endl;
	for (int i = 0; i < player->getTerritory().size(); i++)
	{
		cout << i << ". " << player->getTerritory().at(i)->getTname() << " (" << player->getTerritory().at(i)->getArmyAmount() << ")" << endl;
	}
}

vector<Territory*> HumanPlayerStrategy::GetEnemyTerritory()
{
	vector<Territory*> nonPlayerTerritory;
	
	for each (Territory* territory in player->getMap())
	{
		if (territory->getTerritoryOwner() != player) {
			nonPlayerTerritory.push_back(territory);
		}
	}
	
	return nonPlayerTerritory;
}

set<Player*> HumanPlayerStrategy::GetPlayers()
{
	set<Player*> players;
	for each (Territory* terr in player->getMap())
	{
		if (terr->getTerritoryOwner() != player) {
			players.insert(terr->getTerritoryOwner());
		}
	}
	return players;
}

#pragma endregion

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

	cout << "\nAggressive player deployed/Advanced all its armies and reinforcements until it no longer can." << endl;
}

vector<Territory*> AggressivePlayerStrategy::toAttack()
{
	vector<Territory*> attackList;
	int strongArmy = 0;
	Territory* strongTerritory = 0;

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
	Territory* begin = *player->getTerritory().begin();
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
