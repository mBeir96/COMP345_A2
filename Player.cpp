#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"
#include "Orders.h"
#include "PlayerStrategy.h";
#include <time.h>
#include <algorithm>  
#include <assert.h>  
#include <vector>;
using namespace std;

//Default constructor
Player::Player()
{
	name = "default";
	reinforcementPool = 0;
	territory = *(new vector<Territory *>);
	handCard = new Hand();
	orderList;
	playerTruces = *(new vector<Player*>);
}

//added constructor
Player::Player(string s)
{
	this->name = s;
	reinforcementPool = 0;
	handCard = new Hand();
	orderList;
	territory;
	strategy = NULL;
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
	//delete strategy;

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

void Player::removeTerritory(int i)
{
	this->territory.erase(this->territory.begin() + i);
}

void Player::removeAllTerritories()
{
	int end = this->territory.size();
	for (int i = 0; i < end; i++)
	{
		this->territory.pop_back();
	}
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
	return strategy->toAttack();
}

vector<Territory*> Player::toDefend()
{
	return strategy->toDefend();
}

void Player::issueOrder()
{
	strategy->issueOrder();
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

void Player::setPlayerStrategy(PlayerType type)
{
	switch (type)
	{
	case Human:
		strategy = new HumanPlayerStrategy(this);
		break;
	case Aggressive:
		strategy = new AggressivePlayerStrategy(this);
		break;
	case Benevolent:
		strategy = new BenevolentPlayerStrategy(this);
		break;
	case Neutral:
		strategy = new NeutralPlayerStrategy(this);
		break;
	case Cheater:
		strategy = new CheaterPlayerStrategy(this);
		break;
	default:
		break;
	}
}

void Player::printStrategy()
{
	strategy->PrintStrategy();
}

void Player::removePlayerStrategy()
{
	delete strategy;
}







