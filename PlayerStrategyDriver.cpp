#include "PlayerStrategyDriver.h"
#include "Map.h";
#include "Player.h"
#include "PlayerStrategy.h";
#include "Orders.h";

enum PlayerType;
using namespace std;

void PlayerStrategyDriverMain() {
	
#pragma region 1

#pragma region Simple Map
	Player* none = new Player();
	none->setName("None");

	Territory* t1 = new Territory();
	Territory* t2 = new Territory();
	Territory* t3 = new Territory();
	Territory* t4 = new Territory();

	t1->setTname("Territory 1");
	t2->setTname("Territory 2");
	t3->setTname("Territory 3");
	t4->setTname("Territory 4");

	t1->edges.push_back(t2);
	t1->edges.push_back(t4);
	t2->edges.push_back(t1);
	t2->edges.push_back(t3);
	t3->edges.push_back(t2);
	t3->edges.push_back(t4);
	t4->edges.push_back(t3);
	t4->edges.push_back(t1);

	vector<Territory*>map;
	map.push_back(t1);
	map.push_back(t2);
	map.push_back(t3);
	map.push_back(t4);


#pragma endregion

	/*
#pragma region Cheater
	cout << "Cheater Player testing\n\n";
	Player* cheaterPlayer = new Player();
	cheaterPlayer->setName("Cheater");
	none->setName("None");

	cheaterPlayer->setPlayerStrategy(Cheater);

	t1->setTerritoryOwner(cheaterPlayer);
	t2->setTerritoryOwner(none);
	t3->setTerritoryOwner(none);
	t4->setTerritoryOwner(none);

	cheaterPlayer->setTerritory(t1);
	none->setTerritory(t2);
	none->setTerritory(t3);
	none->setTerritory(t4);

	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);

	cheaterPlayer->issueOrder();

	cout << "\nTerritory after one turn after one turn\n\n";
	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);
	UserPauseStrat();

#pragma 


#pragma endregion

#pragma region Benevolent
	cout << "Benevolent Player testing\n\n";
	Player* peacePlayer = new Player();
	peacePlayer->setName("Peace");
	none->setName("None");

	peacePlayer->setPlayerStrategy(Benevolent);

	t1->setTerritoryOwner(peacePlayer);
	t2->setTerritoryOwner(peacePlayer);
	t3->setTerritoryOwner(peacePlayer);
	t4->setTerritoryOwner(peacePlayer);

	t1->setArmyAmount(1);
	t2->setArmyAmount(0);
	t3->setArmyAmount(0);
	t4->setArmyAmount(4);

	peacePlayer->setTerritory(t1);
	peacePlayer->setTerritory(t2);
	peacePlayer->setTerritory(t3);
	peacePlayer->setTerritory(t4);

	ShowTerritoryArmy(t1);
	ShowTerritoryArmy(t2);
	ShowTerritoryArmy(t3);
	ShowTerritoryArmy(t4);

	peacePlayer->setReinforcementPool(10);
	peacePlayer->issueOrder();
	executePlayerOrders(peacePlayer);

	cout << "\nTerritory after one turn after one turn\n\n";
	ShowTerritoryArmy(t1);
	ShowTerritoryArmy(t2);
	ShowTerritoryArmy(t3);
	ShowTerritoryArmy(t4);
	UserPauseStrat();


#pragma endregion

#pragma region Aggressive
	cout << "Aggressive Player testing\n\n";
	Player* aggressiveplayer = new Player();
	aggressiveplayer->setName("Aggressive Player");
	aggressiveplayer->setPlayerStrategy(Aggressive);

	t1->setTerritoryOwner(aggressiveplayer);
	t2->setTerritoryOwner(aggressiveplayer);
	t3->setTerritoryOwner(none);
	t4->setTerritoryOwner(none);

	t1->setArmyAmount(1);
	t2->setArmyAmount(0);
	t3->setArmyAmount(0);
	t4->setArmyAmount(0);

	aggressiveplayer->setTerritory(t1);
	aggressiveplayer->setTerritory(t2);
	none->setTerritory(t3);
	none->setTerritory(t4);

	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);

	aggressiveplayer->setReinforcementPool(10);
	aggressiveplayer->issueOrder();
	executePlayerOrders(aggressiveplayer);

	cout << "\nTerritory after one turn after one turn\n\n";
	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);
	UserPauseStrat();

#pragma endregion

#pragma region Neutral
	cout << "NeutralPlayer Player testing\n\n";
	Player* neutralPlayer = new Player();
	neutralPlayer->setName("Neutral Player");
	neutralPlayer->setPlayerStrategy(Neutral);

	t1->setTerritoryOwner(neutralPlayer);
	t2->setTerritoryOwner(neutralPlayer);
	t3->setTerritoryOwner(none);
	t4->setTerritoryOwner(none);

	t1->setArmyAmount(2);
	t2->setArmyAmount(0);
	t3->setArmyAmount(0);
	t4->setArmyAmount(0);

	neutralPlayer->setTerritory(t1);
	neutralPlayer->setTerritory(t2);
	none->setTerritory(t3);
	none->setTerritory(t4);

	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);

	neutralPlayer->setReinforcementPool(10);
	neutralPlayer->issueOrder();
	executePlayerOrders(neutralPlayer);

	cout << "\nTerritory after one turn after one turn\n\n";
	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);

	t1->setArmyAmount(1);

	cout << "\nTerritory after neutralPlayer is attacked turn after one turn\n\n";
	neutralPlayer->setReinforcementPool(10);
	neutralPlayer->issueOrder();
	executePlayerOrders(neutralPlayer);

	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);

	UserPauseStrat();
#pragma endregion


#pragma region 2

	int input = 0;
	Player* choicePlayer = new Player();
	PlayerType t;
	//shows that player strategy can be changed during play
	while (input < 5 && input >= 0) {
		switch (input)
		{
		case 0:
			t = Human;
			break;
		case 1:
			t = Aggressive;
			break;
		case 2:
			t = Benevolent;
			break;
		case 3:
			t = Neutral;
			break;
		case 4:
			t = Cheater;
			break;
		default:
			break;
		}

		cout << "Current Strategy: ";
		choicePlayer->setPlayerStrategy(t);
		choicePlayer->printStrategy();
		//choicePlayer->removePlayerStrategy();
		cout << "0: Human Strategy\n";
		cout << "1: Aggressive Strategy\n";
		cout << "2: Benevolent Strategy\n";
		cout << "3: Neutral Strategy\n";
		cout << "4: Cheater Strategy\n";
		cin >> input;
	}
#pragma endregion
*/

#pragma region 3

	cout << "Human Player testing\n\n";
	Player* humanPlayer = new Player();
	humanPlayer->setName("Human Player");
	humanPlayer->setPlayerStrategy(Human);

	Player* neutralPlayer2 = new Player();
	neutralPlayer2->setName("Neutral Player");
	neutralPlayer2->setPlayerStrategy(Neutral);

	humanPlayer->setNeutralPlayer(neutralPlayer2);
	humanPlayer->setMap(map);

	t1->setTerritoryOwner(humanPlayer);
	t2->setTerritoryOwner(humanPlayer);
	t3->setTerritoryOwner(none);
	t4->setTerritoryOwner(none);

	t1->setArmyAmount(2);
	t2->setArmyAmount(0);
	t3->setArmyAmount(5);
	t4->setArmyAmount(0);

	humanPlayer->setTerritory(t1);
	humanPlayer->setTerritory(t2);
	none->setTerritory(t3);
	none->setTerritory(t4);

	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);

	ShowTerritoryArmy(t1);
	ShowTerritoryArmy(t2);
	ShowTerritoryArmy(t3);
	ShowTerritoryArmy(t4);


	humanPlayer->setReinforcementPool(10);
	humanPlayer->issueOrder();
	executePlayerOrders(humanPlayer);

	ShowTerritoryOwner(t1);
	ShowTerritoryOwner(t2);
	ShowTerritoryOwner(t3);
	ShowTerritoryOwner(t4);

	ShowTerritoryArmy(t1);
	ShowTerritoryArmy(t2);
	ShowTerritoryArmy(t3);
	ShowTerritoryArmy(t4);
	UserPauseStrat();


#pragma endregion

}

void UserPauseStrat() {
	int x;
	cout << "\nEnter any number to proceed to testing Player Strategy testing\n";
	cin >> x;
	
}

void ShowTerritoryOwner(Territory* t) {
	cout << t->getTname() << " Owner :" << t->getTerritoryOwner()->getName() << "\n";
}

void ShowTerritoryArmy(Territory* t) {
	cout << t->getTname() << " Army :" << t->army << "\n";
}

void executePlayerOrders(Player* player) {
	for (int i = 0; i < player->getOrderList().size(); i++)
	{
		player->getOrderList().at(i)->execute();
	}
}
	