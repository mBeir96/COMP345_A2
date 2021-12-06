#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Player.h"
#include "Map.h"
using namespace std;

class Territory;
class Player;


enum PlayerType
{
	Human,
	Aggressive,
	Benevolent,
	Neutral,
	Cheater
};

//abstract Playerstrategy class
class PlayerStrategy
{
public:
	PlayerStrategy& operator = (const PlayerStrategy&); //added;
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int) = 0;
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder() = 0;
	virtual vector<Territory*> toAttack() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual void PrintStrategy() = 0;

};

//ConcreteStrategy classes
class HumanPlayerStrategy : virtual public PlayerStrategy {
public:
	HumanPlayerStrategy(Player*);
	~HumanPlayerStrategy();
	HumanPlayerStrategy(const HumanPlayerStrategy& p); //Copy constructor
	HumanPlayerStrategy& operator = (const HumanPlayerStrategy&); //added;
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder() ;
	vector<Territory*> toAttack() ;
	vector<Territory*> toDefend();
	void PrintStrategy();
private:
	Player* player;
};

class AggressivePlayerStrategy : virtual public PlayerStrategy {
public:
	AggressivePlayerStrategy(Player* p);
	~AggressivePlayerStrategy();
	AggressivePlayerStrategy(const AggressivePlayerStrategy& p); //Copy constructor
	AggressivePlayerStrategy& operator = (const AggressivePlayerStrategy&); //added;
	vector<Territory*> getTerritoryNeighbor(Territory*);
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
	void PrintStrategy();

private:
	Player* player;
};

class BenevolentPlayerStrategy : virtual public PlayerStrategy {
public:
	BenevolentPlayerStrategy(Player*);
	~BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& p); //Copy constructor
	BenevolentPlayerStrategy& operator = (const BenevolentPlayerStrategy&); //added
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder() ;
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
	void PrintStrategy();

private:
	Player* player;
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy(Player* player);
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
	void PrintStrategy();
	~NeutralPlayerStrategy();
private:
	Player* player;
	int territoryCount;
	int armyCount;
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
	CheaterPlayerStrategy(Player* player);
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
	void PrintStrategy();
private:
	Player* player;
};
