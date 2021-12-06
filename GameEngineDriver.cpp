#include "GameEngine.h"
#include "CommandProcessing.h"
#include "Player.h";
#include "Orders.h";
#include "Map.h";
#include <iostream>
#include <string>
#include "OrderDriver.h";
#include "PlayerStrategyDriver.h"
using namespace std;


/*gameEngine::gameEngine() {
	this->StartUp = true;
	this-> Play = false;
}*/

int main() {
	PlayerStrategyDriverMain();
	//orderDriver();
	//RiskState currentState = START;
	//GameEngine gm;
	//gm.StartupPhase();
}
