#include "GameEngine.h"
#include <iostream>
#include <string>


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

bool GameEngine::getStartUp(){
    return StartUp;
}
bool GameEngine::getPlay(){
    return Play;
}
void GameEngine::setStartUp(bool StartUp){
    this->StartUp = StartUp;
}
void GameEngine::setPlay(bool Play){
    this->Play = Play;
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
void GameEngine::endExecuteOrder(){
	//add code here later 
}
void GameEngine::win() {
	//add code here later 
}