#include "PlayerStrategy.h"
#include "Player.h"

class PlayerStrategy;

using namespace std;

int main() {
	Player* player = new Player();
	Player* player1 = new Player();
	Player* player2 = new Player();
	Player* player3 = new Player();
	Player* player4 = new Player();
	Player* player5 = new Player();

	// Here: Different players can be assigned different strategies that lead to
	// different behavior using the Strategy design pattern.
	HumanPlayerStrategy* newPlayer1 = new HumanPlayerStrategy(player);
	player1->setStrategy(newPlayer1);

	AggressivePlayerStrategy* newPlayer2 = new AggressivePlayerStrategy(player);
	player3->setStrategy(newPlayer2);
	player3->issueOrder();

	BenevolentPlayerStrategy* newPlayer3 = new BenevolentPlayerStrategy(player);
	player4->setStrategy(newPlayer3);
	player4->issueOrder();

	NeutralPlayerStrategey* newPlayer4 = new NeutralPlayerStrategey(player);
	player2->setStrategy(newPlayer4);
	player2->issueOrder();

	CheaterPlayerStrategey* newPlayer5 = new CheaterPlayerStrategey(player);
	player5->setStrategy(newPlayer5);
	player5->issueOrder();

	// change player type
	player2->setStrategy(newPlayer3);

	// human player uses issueOrder to excute orders up to the user
	player1->issueOrder();

	//delete player;
	//delete player1;
	//delete player2;
	//delete player3;
	//delete player4;
	//delete player5;
}