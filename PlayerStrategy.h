#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Player.h"

//abstract Playerstrategy class
class PlayerStrategy
{
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder(string) = 0;
	virtual void toAttack() = 0;
	virtual void toDenfend() = 0;

};

//ConcreteStrategy classes
class HumanPlayerStrategy: public PlayerStrategy {

	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string) = 0;
	void toAttack() = 0;
    void toDenfend() = 0;
};

class AggressivePlayerStrategy : public PlayerStrategy {
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string) = 0;
	void toAttack() = 0;
	void toDenfend() = 0;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string) = 0;
	void toAttack() = 0;
	void toDenfend() = 0;
};

class NeutralPlayerStrategey : public PlayerStrategy {
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder(string);
	virtual void toAttack();
	virtual void toDenfend();
};

class CheaterPlayerStrategey : public PlayerStrategy {
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder(string);
	virtual void toAttack();
	virtual void toDenfend();
};




