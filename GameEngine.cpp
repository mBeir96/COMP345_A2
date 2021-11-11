#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;


GameEngine::GameEngine()
{
    this->StartUp = false;
    this->Play = false;
}

GameEngine::GameEngine(bool StartUp, bool Play)
{
    this->StartUp = StartUp;
    this->Play = Play;
}


GameEngine::GameEngine(const GameEngine& g)
{
    StartUp = new bool(g.StartUp);
    Play = new bool(g.Play);
}

GameEngine::~GameEngine()
{
    std::cout << "The object is destroy..." << std::endl;
}

GameEngine& GameEngine::operator=(const GameEngine& g)
{
    if (this == &g)
    {
        return *this;
    }
    StartUp = new bool(g.StartUp);
    Play = new bool(g.Play);

    return *this;
}

std::ostream& operator<<(std::ostream& out, const GameEngine& g)
{
    out << g.StartUp << " " << g.Play << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, GameEngine& g)
{
    return in;
}
int state;
void GameEngine::Start() {
    cout << "Welcome to the game " << endl;
    cout << "Enter \"start\" to start the game" << endl;

    string a;
    cin >> a;
    if (a == "start") {
        cout << "CURRENT STATUS" << endl;
        cout << "START" << endl;
        state = 1;
    }

}

void GameEngine::MapLoaded() {
    cout << "Enter \"validMap\" to the next state, \"repeat\" to repeat" << endl;
    string isValid;
    cin >> isValid;

    if (isValid == "repeat") {
        state = 1;
    }
    else if (isValid == "validMap") {
        state = 2;
    }
    //if its invalid
    else if (isValid != "validMap") {
        state = 1;
    }

}
void GameEngine::MapValidated() {
    cout << "Enter \"continue\" " << endl;

    string a;
    cin >> a;
    if (a == "continue") {
        cout << "CURRENT STATUS" << endl;
        cout << "Map validated" << endl;
        state = 3;
    }
}
void GameEngine::PlayersAdded() {
    cout << "Enter \"addplayer\" to add player, \"reinforcement\" to the next state" << endl;
    string a;
    cin >> a;
    if (a == "addplayer") {
        cout << "CURRENT STATUS" << endl;
        cout << "Player Added" << endl;
        cout << "How many players do u want to add " << endl;
        int numberOfPlayers;
        string name;
        cin >> numberOfPlayers;
        /*Player arr [numberOfPlayers];
        for(int i =0;i<numberOfPlayers;i++){
          cout<< "Enter Player " << i+1 << "'s name" << endl;
          cin >> name;
          arr[i](name);
        }*/
        state = 3;
    }
    else if (a == "reinforcement") {

        state = 4;
    }
}
void GameEngine::AssignReinforcement() {

    cout << "Enter \"continue\" " << endl;
    string a;
    cin >> a;
    if (a == "continue") {
        cout << "CURRENT STATUS" << endl;
        cout << "assignReignforcemnent" << endl;
        state = 5;
    }

}
void GameEngine::IssueOrders() {
    cout << "Enter \"yes\" or \"no\" " << endl;
    string a;
    cin >> a;
    if (a == "yes") {
        cout << "CURRENT STATUS" << endl;
        cout << "Issue Order" << endl;
        state = 5;
    }
    else if (a == "no") {
        state = 6;
    }

}
void GameEngine::ExecuteOrders() {
    cout << "Enter \"win\" to win,  Enter \"executeOrder\" to repeat executeOrder Enter \"new\"to go back to assignforcement" << endl;
    string a;
    cin >> a;
    if (a == "win") {

        state = 7;
    }
    else if (a == "executeOrder") {
        state = 6;
    }
    else if (a == "new") {
        state = 5;
    }
}
void GameEngine::Win() {

    cout << "Enter \"playagain\" to repaet,  Enter \"quit\" to get high" << endl;
    string a;
    cin >> a;
    if (a == "playagain") {

        state = 0;
    }
    else if (a == "quit") {
        cout << "u win" << endl;
        state = 8;
    }

}


void GameEngine::States() {
    while (state == 0) {
        Start();
        while (state == 1) {
            MapLoaded();
        }
        while (state == 2) {
            MapValidated();
        }
        while (state == 3) {
            PlayersAdded();
        }
        while (state == 4) {
            AssignReinforcement();
            while (state == 5) {
                IssueOrders();
            }
            while (state == 6) {
                ExecuteOrders();
            }
            while (state == 7) {
                Win();
            }
        }

    }
}






bool GameEngine::getStartUp() {
    return StartUp;
}
bool GameEngine::getPlay() {
    return Play;
}
void GameEngine::setStartUp(bool StartUp) {
    this->StartUp = StartUp;
}
void GameEngine::setPlay(bool Play) {
    this->Play = Play;
}

void GameEngine::currentState() {

}

void GameEngine::changeState() {

}


void GameEngine::loadMap() {
    //add code here later 
}
void GameEngine::validateMap() {
    //add code here later 
}
void GameEngine::addPlayer() {
    //add code here later 
}
void GameEngine::issueOrder() {
    //add code here later 
}
void GameEngine::executeOrder() {
    //add code here later 
}
void GameEngine::endExecuteOrder() {
    //add code here later 
}
void GameEngine::win() {
    //add code here later 
}
