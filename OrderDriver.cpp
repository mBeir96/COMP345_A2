#include "GameEngine.h"
#include "CommandProcessing.h"
#include "Player.h";
#include "Orders.h";
#include "Map.h";
#include <iostream>  
#include "OrderDriver.h";
#include <windows.h>

using namespace std;

/*gameEngine::gameEngine() {
	this->StartUp = true;
	this-> Play = false;
}*/



void orderDriver() {

#pragma region Initialization

	Player* p1 = new Player();
	p1->setName("Player1");
	Player* p2 = new Player();
	p2->setName("Player2");
	//player1 territories
	Territory* t1 = new Territory();
	Territory* t2 = new Territory();
	Territory* t3 = new Territory();

	//player1 Territories
	Territory* t4 = new Territory();
	Territory* t5 = new Territory();
	Territory* t6 = new Territory();

	t1->setTname("Territory 1");
	t2->setTname("Territory 2");
	t3->setTname("Territory 3");
	t4->setTname("Territory 4");
	t5->setTname("Territory 5");
	t6->setTname("Territory 6");

	//set all edges
	t1->edges.push_back(t2);
	t1->edges.push_back(t6);

	t2->edges.push_back(t1);
	t2->edges.push_back(t3);

	t3->edges.push_back(t2);
	t3->edges.push_back(t4);

	t4->edges.push_back(t3);
	t4->edges.push_back(t5);

	t5->edges.push_back(t4);
	t5->edges.push_back(t6);

	t6->edges.push_back(t5);
	t6->edges.push_back(t1);

	//set all army amounts
	t1->setArmyAmount(1);
	t2->setArmyAmount(2);
	t3->setArmyAmount(3);
	t4->setArmyAmount(1);
	t5->setArmyAmount(2);
	t6->setArmyAmount(3);

	//give player 1 territories
	vector<Territory*> *t = new vector<Territory*>;
	t->push_back(t1);
	t->push_back(t2);
	t->push_back(t3);

	p1->setTerritory(t1);
	t1->setTerritoryOwner(p1);
	p1->setTerritory(t2);
	t2->setTerritoryOwner(p1);
	p1->setTerritory(t3);
	t3->setTerritoryOwner(p1);
	

	//give player 2 territories
	p2->setTerritory(t4);
	t4->setTerritoryOwner(p2);
	p2->setTerritory(t5);
	t5->setTerritoryOwner(p2);
	p2->setTerritory(t6);
	t6->setTerritoryOwner(p2);

	cout << "Player1 owns territory 1, 2 and 3\n";
	cout << "Player2 owns territory 4, 5 and 6\n";
	cout << "The Territories are cirular\nTherefore 1 is adjacent to 2 which is adjacent to 3 and so on and so forth";
	userPause();

#pragma endregion

#pragma region Deploy test

	
	cout << "Deploy Orders Test...\n\n";
	
	cout << "Attempting to Deploy to 6\n";
	timePause();
	DeployOrders* dep1 = new DeployOrders();
	dep1->setSelfPlayers(p1);
	dep1->setTargetTerritory(t6);
	dep1->execute();
	userPause();

	cout << "\nAttempting to Deploy to 2\n";
	cout << "\nPrevious Terr2 army: " << t2->getArmyAmount();
	cout << "\n";
	timePause();
	DeployOrders* dep2 = new DeployOrders();
	dep2->setSelfPlayers(p1);
	dep2->setNumArmy(1);
	dep2->setTargetTerritory(t2);
	dep2->execute();

	cout << "\Current Terr2 army: " << t2->getArmyAmount() << "\n";
	userPause();
#pragma endregion

#pragma region Airlift test

	cout << "\n\nAirlift Orders Test...\n\n";

	cout << "Attempting to move from 6 to 1\n";
	timePause();
	AirliftOrders* air1 = new AirliftOrders();
	air1->setSelfPlayers(p2);
	air1->setSourceTerritory(t6);
	air1->setTargetTerritory(t1);
	air1->execute();
	userPause();

	cout << "\nAttempting to move from 6 to 4\n";
	cout << "\nPrevious Terr6 army: " << t6->getArmyAmount() << "\n";
	cout << "Previous Terr4 army: " << t4->getArmyAmount() << "\n";

	timePause();
	AirliftOrders* air2 = new AirliftOrders();
	air2->setSelfPlayers(p2);
	air2->setSourceTerritory(t6);
	air2->setTargetTerritory(t4);
	air2->setNumArmy(2);
	air2->execute();

	cout << "\Current Terr6 army: " << t6->getArmyAmount() << "\n";
	cout << "\Current Terr4 army: " << t4->getArmyAmount() << "\n";

	userPause();
#pragma endregion

#pragma region Bomb test

	cout << "\n\Bomb Orders Test...\n\n";

	cout << "Attempting to bomb Terr3 as Player1\n";
	timePause();
	BombOrders* bomb1 = new BombOrders();
	bomb1->setSelfPlayers(p1);
	bomb1->setTargetTerritory(t3);
	bomb1->execute();
	userPause();

	cout << "\Attempting to bomb Terr4 as Player1\n";
	cout << "Previous Terr4 army: " << t4->getArmyAmount() << "\n";

	timePause();
	BombOrders* bomb2 = new BombOrders();
	bomb2->setSelfPlayers(p1);
	bomb2->setTargetTerritory(t4);
	bomb2->execute();

	cout << "\Current Terr4 army: " << t4->getArmyAmount() << "\n";
	userPause();
#pragma endregion

#pragma region Advance test

	cout << "\n\Advance Orders Test...\n\n";

	cout << "Attempting to move to Terr3 from Terr1 as Player1\n";
	timePause();
	AdvanceOrders* adv1 = new AdvanceOrders();
	adv1->setSelfPlayers(p1);
	adv1->setTargetTerritory(t3);
	adv1->setSourceTerritory(t1);
	adv1->execute();
	userPause();

	cout << "\Attempting to move Terr3 from Terr2 as Player1\n";
	cout << "Previous Terr3 army: " << t3->getArmyAmount() << "\n";
	cout << "Previous Terr2 army: " << t2->getArmyAmount() << "\n";

	timePause();
	AdvanceOrders* adv2 = new AdvanceOrders();
	adv2->setSelfPlayers(p1);
	adv2->setSourceTerritory(t2);
	adv2->setTargetTerritory(t3);
	adv2->setArmyUnits(2);
	adv2->execute();

	cout << "\Current Terr3 army: " << t3->getArmyAmount() << "\n";
	cout << "\Current Terr2 army: " << t2->getArmyAmount() << "\n";

	userPause();

	cout << "\Attacking Terr4 from Terr3 as Player1\n";
	cout << "Previous Terr4 army: " << t4->getArmyAmount() << "\n";
	cout << "Previous Terr3 army: " << t3->getArmyAmount() << "\n";

	timePause();
	AdvanceOrders* adv3 = new AdvanceOrders();
	adv3->setSelfPlayers(p1);
	adv3->setSourceTerritory(t3);
	adv3->setTargetTerritory(t4);
	adv3->setArmyUnits(5);
	adv3->execute();

	cout << "\Current Terr4 army: " << t4->getArmyAmount() << "\n";
	cout << "\Current Terr3 army: " << t3->getArmyAmount() << "\n";

	userPause();

#pragma endregion

#pragma region Negotiate test

	cout << "\n\Negotiate Orders Test...\n\n";

	cout << "Attempting truce with player2 as player2\n";
	timePause();
	NegotiateOrders* neg1 = new NegotiateOrders();
	neg1->setSelfPlayers(p2);
	neg1->setPeacePlayer(p2);
	neg1->execute();
	userPause();

	cout << "\nAttempting truce with player1 as player2\n";

	timePause();
	NegotiateOrders* neg2 = new NegotiateOrders();
	neg2->setSelfPlayers(p2);
	neg2->setPeacePlayer(p1);
	neg2->execute();

	userPause();

	cout << "\Attempting to bomb Terr5 as Player1 during truce\n";
	cout << "Previous Terr5 army: " << t5->getArmyAmount() << "\n";

	timePause();
	BombOrders* bomb3 = new BombOrders();
	bomb3->setSelfPlayers(p1);
	bomb3->setTargetTerritory(t5);
	bomb3->execute();

	cout << "\Current Terr5 army: " << t5->getArmyAmount() << "\n";
	userPause();

	cout << "\Attacking Terr5 from Terr4 as Player1 during truce\n";
	cout << "Previous Terr5 army: " << t5->getArmyAmount() << "\n";
	cout << "Previous Terr4 army: " << t4->getArmyAmount() << "\n";

	timePause();
	AdvanceOrders* adv4 = new AdvanceOrders();
	adv4->setSelfPlayers(p1);
	adv4->setSourceTerritory(t4);
	adv4->setTargetTerritory(t5);
	adv4->setArmyUnits(5);
	adv4->execute();

	cout << "\Current Terr5 army: " << t5->getArmyAmount() << "\n";
	cout << "\Current Terr4 army: " << t4->getArmyAmount() << "\n";

	userPause();

#pragma endregion

#pragma region Blockade Test
	Player* neutPlayer = new Player();
	neutPlayer->setName("NeutralPlayer");

	cout << "\n\Blockade Orders Test...\n\n";

	cout << "Attempting to Blockade Terr6 as Player1\n";
	timePause();
	BlockadeOrders* bloc1 = new BlockadeOrders();
	bloc1->setSelfPlayers(p1);
	bloc1->setTargetTerritory(t6);
	bloc1->setNeutralPlayer(neutPlayer);
	bloc1->execute();
	userPause();

	cout << "\Attempting to bomb Blockade Terr4 as Player1\n";
	cout << "Previous Terr4 army: " << t4->getArmyAmount() << "\n";
	cout << "Current Terr4 owner " << t4->player->getName() << "\n";

	timePause();
	BlockadeOrders* bloc2 = new BlockadeOrders();
	bloc2->setSelfPlayers(p1);
	bloc2->setTargetTerritory(t4);
	bloc2->setNeutralPlayer(neutPlayer);
	bloc2->execute();

	cout << "\Current Terr4 army: " << t4->getArmyAmount() << "\n";
	cout << "Current Terr4 owner " << t4->player->getName() << "\n";
	userPause();

#pragma endregion


}

void userPause() {
	int x;
	cout << "\nEnter any number to proceed to testing orders testing\n";
	cin >> x;
}

void timePause() {
	Sleep(100);
}

