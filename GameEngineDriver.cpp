#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;


/*gameEngine::gameEngine() {
	this->StartUp = true;
	this-> Play = false;
}*/

int main() {

	RiskState currentState = START;
	GameEngine gm;
	gm.States();
	return 0;
}
