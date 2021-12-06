#include "PlayerStrategyDriver.h"
#include "Map.h";
#include "Player.h"
#include "PlayerStrategy.h";
enum PlayerType;
using namespace std;

void PlayerStrategyDriverMain() {
	
#pragma region 1

#pragma region Cheater
	cout << "Cheater Player testing\n\n";
	Player* cheaterPlayer = new Player();
	Player* none = new Player();
	cheaterPlayer->setName("Cheater");
	none->setName("None");

	cheaterPlayer->setPlayerStrategy(Cheater);

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

#pragma region 3


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

