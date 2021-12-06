#include "PlayerStrategyDriver.h"
#include "Map.h";
#include "Player.h"
#include "PlayerStrategy.h";
enum PlayerType;
using namespace std;

void PlayerStrategyDriverMain() {
	
#pragma region 1

#pragma endregion

#pragma region 2

	int input = 0;
	Player* choicePlayer = new Player();
	PlayerType* t;
	//shows that player strategy can be changed during play
	while (input < 5 && input >= 0) {
		switch (input)
		{
		case 0 :
			*t = Human;
			break;
		case 1:
			*t = Aggressive;
			break;
		case 2:
			*t = Benevolent;
			break;
		case 3:
			*t = Neutral;
			break;
		case 4:
			*t = Cheater;
			break;
		default:
			break;
		}

		cout << "Current Strategy: ";
		choicePlayer->setPlayerStrategy(*t);
		choicePlayer->printStrategy();
		choicePlayer->removePlayerStrategy();
		cout << "0: Human Strategy\n";
		cout << "1: Aggressive Strategy\n";
		cout << "2: Benevolent Strategy\n";
		cout << "3: Neutral Strategy\n";
		cout << "4: Cheater Strategy\n";
		cin >> input;
	}

	delete choicePlayer;
	delete t;

#pragma endregion

#pragma region 3

#pragma region Cheater
	Player* cheaterPlayer = new Player();
	cheaterPlayer->setName("Cheater");

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

	delete t1, t2, t3, t4, cheaterPlayer;
#pragma 

#pragma endregion

}

void userPauseStrat() {
	int x;
	cout << "\nEnter any number to proceed to testing orders testing\n";
	cin >> x;
}

