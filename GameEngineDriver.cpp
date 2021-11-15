#include "GameEngine.h"
#include "CommandProcessing.h"
#include "Player.h";
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
	gm.StartupPhase();

	cout << "Hello";
}
