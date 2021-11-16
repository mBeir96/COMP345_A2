#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"
#include "Orders.h"

#include <time.h>
#include <algorithm>  
#include <assert.h>  
using namespace std;

//Default constructor
Player::Player()
{
	name = "default";
	reinforcementPool = 0;
	territory;
	handCard = new Hand();
	orderList;
}

//added constructor
Player::Player(string s)
{
	this->name = s;
	reinforcementPool = 0;
	handCard = new Hand();
	orderList;
	territory;
}


//Four parmeter constructor
Player::Player(int reinforcementPool, string name, vector<Territory*> t, Hand* h, vector<Orders*> o)
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
	if (this == &player)
	{
    	return *this;
    }
	this->name = player.name;
	this->reinforcementPool = player.reinforcementPool;
	this->territory = player.territory;
	this->handCard = player.handCard;
	this->orderList = player.orderList;
	return *this;
}

bool Player::operator==(const Player& player)
{
	if (name == player.name && reinforcementPool == player.reinforcementPool)
	{
		if(territory.size() == player.territory.size() && handCard->cards->size() == player.handCard->cards->size() && orderList.size() == player.orderList.size())
		{
			for(int i = 0; i < (int)territory.size(); i++)
			{
				if(territory.at(i) == player.territory.at(i))
				{
					continue;
				}
				return false;
			}

			for(int i = 0; i < (int)handCard->cards->size(); i++)
			{
				if(handCard->cards->at(i) == player.handCard->cards->at(i))
				{
					continue;
				}
				return false;
			}

			for(int i = 0; i < (int)orderList.size(); i++)
			{
				if(orderList.at(i) == player.orderList.at(i))
				{
					continue;
				}
				return false;
			}
			return true;
		}
		return false;	
    }
	
	return false;
}


std::ostream& operator<<(std::ostream& out, const Player& p)
{	
	p.handCard->ShowCards();
	out << p.name << p.reinforcementPool << p.territory.at(0) << p.orderList.at(0);
    return out;
}

std::istream& operator>>(std::istream& in, Player& p)
{
    return in;
}

//Destructor
Player::~Player()
{

	if (handCard != NULL)
	{
		delete handCard;
		handCard = NULL;
	}
	
	if (!orderList.empty())
	{
		for (auto order : orderList)
		{
			delete order;
			order = NULL;
		}
	}
	

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

void Player::setTerritory(Territory *t)
{

	this->territory.push_back(t);
}

void Player::setHand(Card* c)
{
	this->handCard->AddCard(c);
}

vector<Territory*> Player::getTerritory()
{
	return territory;

}


Hand* Player::getCard()
{

	return handCard;
}

vector<Territory*> Player::toAttack()
{
	vector<Territory*> AttackList;

	for (int i = 0; i < territory.size(); i++)
	{
		string temp = getName();
		if (!temp.compare(territory[i]->getTerritoryOwner()->getName()) == 0)
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
			if (getName().compare(territory[i]->getTerritoryOwner()->getName()) == 0)

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
		AttackList[actionNumber1]->setTerritoryOwner(AttackList[actionNumber1]->getTerritoryOwner());
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

//void Player::printOrder()
//{

	//for (int i = 0; i < orderList.size(); i++) {
	//	cout << "<" << orderList.at(i)->getResult() << "> ";
	//}
	//cout << endl;
//}

void Player::printHandcard()
{



}

void Player::addTruce(Player* player)
{
	playerTruces.push_back(player);
}

void Player::removeAllTruces()
{
	/*for (int i = 0; i < playerTruces.size(); i++)
	{
		delete(playerTruces.at(i));
	}*/
	playerTruces.clear();
}

bool Player::hasTruce(Player* player)
{
	for (int i = 0; i < playerTruces.size(); i++)
	{
		if (playerTruces.at(i) == player)
		{
			return true;
		}
	}
	return false;
}





