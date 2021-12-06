#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"


class Player;
using namespace std;

//need to define constructors in cpp file 

//abstract Playerstrategy class
class PlayerStrategy
{
public:
	Player* player;
	PlayerStrategy();// maybe delete constructors???
	~PlayerStrategy();
	PlayerStrategy(const PlayerStrategy& p); //Copy constructor
	PlayerStrategy& operator = (const PlayerStrategy&); //added;
	//create method that will change strategy in the isuueing orders phase
	virtual int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	virtual void issueOrder(string) = 0;
	virtual vector<Territory*> toAttack() = 0;
	virtual vector<Territory*> toDenfend() = 0;

};

//ConcreteStrategy classes  
class HumanPlayerStrategy : virtual public PlayerStrategy {


	HumanPlayerStrategy(Player*);

	HumanPlayerStrategy();
	~HumanPlayerStrategy();
	HumanPlayerStrategy(const HumanPlayerStrategy& p); //Copy constructor
	HumanPlayerStrategy& operator = (const HumanPlayerStrategy&); //added;
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string) ;
	vector<Territory*> toAttack() ;
	vector<Territory*> toDenfend();
};

class AggressivePlayerStrategy : virtual public PlayerStrategy {

	AggressivePlayerStrategy(Player* p);

	AggressivePlayerStrategy();
	~AggressivePlayerStrategy();
	AggressivePlayerStrategy(const AggressivePlayerStrategy& p); //Copy constructor
	AggressivePlayerStrategy& operator = (const AggressivePlayerStrategy&); //added;

	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string) ;
	vector<Territory*> toAttack();
	vector<Territory*> toDenfend();
};

class BenevolentPlayerStrategy : virtual public PlayerStrategy {

	BenevolentPlayerStrategy(Player*);

	BenevolentPlayerStrategy();
	~BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& p); //Copy constructor
	BenevolentPlayerStrategy& operator = (const BenevolentPlayerStrategy&); //added

	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() 
	void issueOrder(string) ;
	vector<Territory*> toAttack();
	vector<Territory*> toDenfend();
};

class NeutralPlayerStrategey : virtual public PlayerStrategy {

    NeutralPlayerStrategy(Player*);

	NeutralPlayerStrategey();
	~NeutralPlayerStrategey();
	NeutralPlayerStrategey(const NeutralPlayerStrategey& p); //Copy constructor
	NeutralPlayerStrategey& operator = (const NeutralPlayerStrategey&); //added;

	//create method that will change strategy in the isuueing orders phase
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	void issueOrder(string);
	vector<Territory*> toAttack();
	vector<Territory*> toDenfend();
};

class CheaterPlayerStrategey : virtual public PlayerStrategy {

	CheaterPlayerStrategy(Player*);

	CheaterPlayerStrategey();
	~CheaterPlayerStrategey();
	CheaterPlayerStrategey(const CheaterPlayerStrategey& p); //Copy constructor
	CheaterPlayerStrategey& operator = (const CheaterPlayerStrategey&); //added;

	//create method that will change strategy in the isuueing orders phase
	int changeStrategy(string, int);
	//implement issueOrder(), toAttack(), toDefend() in different ConcreteStrategy 
	void issueOrder(string);
	vector<Territory*> toAttack();
	vector<Territory*> toDenfend();
};