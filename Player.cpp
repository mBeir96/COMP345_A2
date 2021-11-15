#include "Player.h"
#include <time.h>
#include <algorithm>  
#include <assert.h>  
using namespace std;

//Default constructor
Player::Player()
{
	name = "default";
	int reinforcementPool = 0;
	vector<Territory*> territory;
	vector<Card*> handCard;
	vector<Orders*> orderList;
}

//added constructor
Player::Player(string s)
{
	this->name = s;

}


//Four parmeter constructor
Player::Player(int reinforcementPool, string name, vector<Territory*> t, vector<Card*> h, vector<Orders*> o)
{
	this->reinforcementPool = reinforcementPool;
	this->name = name;
	this->territory = t;
	this->handCard = h;
	this->orderList = o;
}



//Copy constructor (Deep copy)
Player::Player(const Player& p)
{
	this->reinforcementPool = p.reinforcementPool;
	this->name = p.name;
	this->territory = p.territory;
	this->handCard = p.handCard;
	this->orderList = p.orderList;

}

//added assignment operator
Player& Player::operator=(const Player& player)
{
	this->name = player.name;
	this->reinforcementPool = player.reinforcementPool;
	this->territory = player.territory;
	this->handCard = player.handCard;
	this->orderList = player.orderList;
	return *this;
}

//Destructor
Player::~Player()
{
	name = "";
	reinforcementPool = 0;
	territory.clear();
	handCard.clear();
	for (auto order : orderList)
	{
		delete order;
	}
	orderList.clear();
	//release memory
	vector<Territory*>().swap(territory);
	vector<Card*>().swap(handCard);
	vector<Orders*>().swap(orderList);
}

//added
string Player::getName() {
	return this->name;
}

void Player::setName(string s) {
	this->name = s;
}

int Player::getReinforcementPool() {
	return this->reinforcementPool;
}

void Player::setReinforcementPool(int i) {
	this->reinforcementPool = i;
}

void Player::setTerritory(Territory t)
{

	this->territory.push_back(&t);
}

vector<Territory*> Player::getTerritory()
{
	return territory;

}


vector<Card*> Player::getCard()
{

	return handCard;
}

vector<Territory*> Player::toAttack()
{
	vector<Territory*> AttackList;

	for (int i = 0; i < territory.size(); i++)
	{
		string temp = getName();
		if (!temp.compare(territory[i]->getTerritoryOwner()) == 0)
			AttackList.push_back(territory[i]);

	}
	cout << "The list of territories that can be Attack by " << getName() << endl;
	for (int i = 0; i < AttackList.size(); i++)
	{
		cout << "Index " << i << " " << (*AttackList[i]).getTname() << " " << (*AttackList[i]).getContinent() << endl;
	}
	return AttackList;
}

vector<Territory*> Player::toDefend()
{
	{
		vector<Territory*> DefendList;

		for (int i = 0; i < territory.size(); i++)
		{
			if (getName().compare(territory[i]->getTerritoryOwner()) == 0)

				DefendList.push_back(territory[i]);
		}

		cout << "The list of territories that can be Defend by " << getName() << endl;
		for (int i = 0; i < DefendList.size(); i++)
		{
			cout << "Index " << i << " " << (*DefendList[i]).getTname() << " " << (*DefendList[i]).getContinent() << endl;
		}
		return DefendList;
	}

}
bool Player::playerContientBouns()
{
	string a = "NA";
	string b = "AS";
	string c = "SA";
	string d = "AU";
	string e = "EU";
	string f = "AF";

	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	for (int i = 0; i < territory.size(); i++)
	{
		string temp = (*territory[i]).getContinent();
		if (temp.compare(a) == 0)
		{
			c1++;
		}
		if (temp.compare(b) == 0)
		{
			c2++;
		}
		if (temp.compare(c) == 0)
		{
			c3++;
		}
		if (temp.compare(d) == 0)
		{
			c4++;
		}
		if (temp.compare(e) == 0)
		{
			c5++;
		}
		if (temp.compare(f) == 0)
		{
			c6++;
		}


	}
	if (c1 == 3) { return true; }//NA 
	if (c2 == 3) { return true; }//AS
	if (c3 == 1) { return true; }//SA
	if (c4 == 1) { return true; }//AU
	if (c5 == 1) { return true; }//EU
	if (c6 == 1) { return true; }//EU



	return false;
}


void Player::issueOrder()
{
	//Display territories that can be attack or defend
	vector<Territory*> AttackList;
	AttackList = toAttack();
	vector<Territory*> DefendList;
	DefendList = toDefend();

	//Deploy order until no armies left	
	while (getReinforcementPool() != 0)
	{
		int army = getReinforcementPool();

		for (int i = 0; i < DefendList.size(); i++)
		{

			int temp = rand() % (army + 1);
			cout << temp << endl;
			temp += DefendList[i]->getArmyAmount();
			DefendList[i]->setArmyAmount(temp);
			army = temp - army;
			setReinforcementPool(army);
			if (army == 1)
			{
				temp = 1;
				temp += DefendList[i]->getArmyAmount();
				DefendList[i]->setArmyAmount(temp);
				setReinforcementPool(0);
			}
		}
	}

	//Advance order Attack

	int actionNumber1 = rand() % AttackList.size();
	int Enemy = AttackList[actionNumber1]->getArmyAmount();

	int actionNumber2 = rand() % DefendList.size();
	int Attack = DefendList[actionNumber2]->getArmyAmount();

	if (Enemy >= Attack)
	{
		Enemy = Enemy - Attack;
		AttackList[actionNumber1]->setArmyAmount(Enemy);
		DefendList[actionNumber2]->setArmyAmount(0);
	}
	else
	{
		Attack = Attack - Enemy;
		AttackList[actionNumber1]->setArmyAmount(Attack);
		DefendList[actionNumber2]->setArmyAmount(0);
		AttackList[actionNumber1]->setTerritoryOwner(getName());
	}
	//Advance order Defend

	int actionNumber3 = rand() % AttackList.size();
	int Defend1 = DefendList[actionNumber1]->getArmyAmount();

	int actionNumber4 = rand() % DefendList.size();
	int Defend2 = DefendList[actionNumber2]->getArmyAmount();

	if (actionNumber3 != actionNumber4)
	{
		DefendList[actionNumber3]->setArmyAmount(0);
		DefendList[actionNumber4]->setArmyAmount(Defend2 + Defend1);
	}

	//Play card

}

vector<Orders*> Player::getOrderList()
{

	return orderList;
}

void Player::setOrder(Orders* a)
{
	orderList.push_back(a);
}

void Player::printOrder()
{

	for (int i = 0; i < orderList.size(); i++) {
		cout << "<" << orderList.at(i)->getResult() << "> ";
	}
	cout << endl;
}

void Player::printHandcard()
{



}






