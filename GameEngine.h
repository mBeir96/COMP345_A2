#pragma once
#include "Map.h"
#include "Orders.h";
#include "Player.h"
#include "CommandProcessing.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

class CommandProcessor;
class FileLineReader;

class Map;
class MapLoader;
class Territory;
class Deck;
class Player;



enum RiskState {
	START, MAPLOADED, MAPVALIDATED, PLAYERSADDED, ASSIGNMENTREIFORCEMENT, ISSUEORDERS, EXECUTEORDERS, WIN
};


class GameEngine : public Subject, public ILoggable
{
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
	int changeState(int state);
	void reinforcmentPhase(); // reinforcment phase part 3.1
	void IssueOrders();
	void issueOrdersPhase();
	void ExecuteOrders();

	//
	Map* theMap;
	MapLoader* loader;
	vector<Territory>* loadedMap;
	vector<Player*> players;


	FileCommandProcessorAdapter processor;
	CommandProcessor* cp = new CommandProcessor();
	FileLineReader* flr = new FileLineReader();

	static int CommandCount;
	ifstream inFile;


	virtual void stringToLog(string l);


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
	
	void executeOrderPhase();
	bool StartUp;
	bool Play;

};

