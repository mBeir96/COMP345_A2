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
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int) = 0;
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder(string) = 0;
	virtual vector<Territory*> toAttack() = 0;
	virtual vector<Territory*> toDefend() = 0;
	

};

//ConcreteStrategy classes
class HumanPlayerStrategy: public PlayerStrategy {
public:
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string);
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	AggressivePlayerStrategy(Player* player);
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string);
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
private:
	Player* player;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string);
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy(Player* player);
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder(string);
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
	~NeutralPlayerStrategy();
private:
	Player* player;
	int* territoryCount;
	int* armyCount;
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
	CheaterPlayerStrategy(Player* player);
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder(string);
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
private:
	Player* player;
};
