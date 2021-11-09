/*
	Program: C++ Assignment 1 team 9
	Author: Adam Mohamad
	Desc: Game Engine
	Date: 9/10/21

*/
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

	while (true) {

		switch (currentState) {
		case START:
			cout << "CURRENT STATUS" << endl;
			cout << "START" << endl;
			//<<<Add code over here >>>

		case MAPLOADED:
			cout << "CURRENT STATUS" << endl;
			cout << "MAP LOADED" << endl;
			int loadmap;
			cin >> loadmap;
			switch (loadmap) {
			case 1:
				currentState = MAPVALIDATED;
				//<<<Add code over here >>>
				break;

				// the loop
			default:
				cout << "MAP LOADED AGAIN" << endl;
				currentState = MAPLOADED;
				//<<<Add code over here >>>
				break;
			}
			break;

		case MAPVALIDATED:
			cout << "CURRENT STATUS" << endl;
			cout << "MAP VALIDATED" << endl;
			//<<<Add code over here >>>

		case PLAYERSADDED:
			cout << "CURRENT STATUS" << endl;
			cout << "PLAYERS ADDED	" << endl;
			int addPlayer;
			cin >> addPlayer;
			switch (addPlayer) {
			case 1:
				currentState = ASSIGNMENTREIFORCEMENT;
				break;
				//<<<Add code over here >>>

				// the loop
			default:
				cout << "ADD PLAYER AGAIN" << endl;
				currentState = PLAYERSADDED;
				//<<<Add code over here >>>
				break;
			}
			break;


		case ASSIGNMENTREIFORCEMENT:
			cout << "CURRENT STATUS" << endl;
			cout << " ASSIGNMENT REIFORCEMENT	" << endl;
			//<<<Add code over here >>>



		case ISSUEORDERS:
			cout << "CURRENT STATUS" << endl;
			cout << " ISSUE		ORDERS" << endl;
			int issueOrder;
			cin >> issueOrder;
			switch (issueOrder) {
			case 1:

				currentState = EXECUTEORDERS;
				//<<<Add code over here >>>
				break;

				// the loop
			default:
				cout << "ISSUE ORDERS AGAIN" << endl;
				currentState = ISSUEORDERS;
				//<<<Add code over here >>>
				break;
			}
			break;

		case EXECUTEORDERS:
			cout << "CURRENT STATUS" << endl;
			cout << " EXECUTE ORDER" << endl;
			//<<<Add code over here >>>

			int executeOrder;
			cin >> executeOrder;
			switch (executeOrder) {
			case 1:
				currentState = WIN;
				break;

				//will go back to ASSIGNMENT REIFORCEMENT
			case 2:
				cout << "CURRENT STATUS" << endl;
				cout << " ASSIGN REIFORCEMENT" << endl;
				currentState = ASSIGNMENTREIFORCEMENT;
				//<<<Add code over here >>>
				break;
				// the loop
			default:
				cout << "EXECUTE ORDERS AGAIN" << endl;
				currentState = EXECUTEORDERS;
				//<<<Add code over here >>>
				break;
			}
			break;
		case WIN:
			cout << "CURRENT STATUS" << endl;
			cout << " WIN " << endl;
			int playAgain;
			cin >> playAgain;
			switch (playAgain) {
			case 1:
				cout << "PLAY AGAIN" << endl;
				currentState = START;
				//<<<Add code over here >>>
				break;

				// Game ended
			default:
				cout << " YOU WIN CONGRATULATION!!!" << endl;
				//<<<Add code over here >>>
				break;
			}
			break;

		default:
			cout << "Error! Invalid State Detected." << endl;
			//<<<Add code over here >>>
			break;
		}

	}
	return 0;
}
