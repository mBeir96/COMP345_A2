#pragma once
#include "GameEngine.h"
#include "CommandProcessing.h"
#include "Map.h"
#include "Orders.h";
#include "Player.h";
#include <iostream>
#include <string>
#include <algorithm>
enum RiskState {
	START, MAPLOADED, MAPVALIDATED, PLAYERSADDED, ASSIGNMENTREIFORCEMENT, ISSUEORDERS, EXECUTEORDERS, WIN
};
class Map;
class MapLoader;
class Territory;
class Deck;

class GameEngine {
public:
	GameEngine();
	GameEngine(bool, bool);
	GameEngine(const GameEngine& g);
	GameEngine& operator=(const GameEngine& g);
	friend std::istream& operator>>(std::istream& in, GameEngine& g);
	friend std::ostream& operator<<(std::ostream& out, const GameEngine& g);
	~GameEngine();
	void loadMap();
	void validateMap();
	void addPlayer();
	void issueOrder();
	void executeOrder();
	void endExecuteOrder();
	void win();
	bool getStartUp();
	bool getPlay();
	void setStartUp(bool);
	void setPlay(bool);
	void currentState();
	void changeState();

	//
	Map* theMap;
	MapLoader* loader;
	vector<Territory>* loadedMap;

	FileCommandProcessorAdapter processor;
	CommandProcessor* cp = new CommandProcessor();
	FileLineReader* flr = new FileLineReader();

	static int CommandCount;
	ifstream inFile;

	vector<Player*> players;

	Deck* deck;

	//states
	void Start();
	void MapLoaded();
	void MapValidated();
	void PlayersAdded();
	void AssignReinforcement();
	void IssueOrders();
	void ExecuteOrders();
	void Win();

	//loops
	void StartupPhase();
	void play();
private:
	bool StartUp;
	bool Play;

};