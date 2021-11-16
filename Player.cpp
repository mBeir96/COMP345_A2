#include "Player.h"
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

void Player::removeTerritory(int i)
{
	this->territory.erase(this->territory.begin() + i);
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
	//check if they are neighbours
	vector<Territory*> AttackList = this->NeighbourT;
	//Order By least amount of armies to attack 
	for (int i = 0; i < AttackList.size(); i++)
	{
		for (int j = 0; j < array.size() - 1; j++)
		{
			//Check swap Value
			if (AttackList[j]->army > AttackList[j + 1]->army)
				swap((AttackList[j]), AttackList[j + 1]);
		}
		

		string temp = getName();
		if (!temp.compare(AttackList[i]->getTerritoryOwner()->getName()) == 0)
			AttackList.push_back(AttackList[i]);

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
	vector<Territory*> DefendList=this->territory;
	
	for (int i = 0; i < territory.size(); i++){
		if (getName().compare(territory[i]->getTerritoryOwner()->getName()) == 0)
			DefendList.push_back(territory[i]);
		}
	
	for (int i = 0; i < DefendList.size(); i++)
	{
		//compare elemet to the next element, and swap if condition is true
		for (int j = 0; j < DefendList.size() - 1; j++)
		{
			//Order By least amount of armies
			//Check swap Value
			if (DefendList[j]->army > DefendList[j + 1]->army)
				swap((DefendList[j]), DefendList[j + 1]);
		}
	}
	cout << "The list of territories that can be Defend by " << getName() << endl;
	for (int i = 0; i < DefendList.size(); i++){
		cout << "Index " << i << " " << (*DefendList[i]).getTname() << " " << (*DefendList[i]).getContinent() << endl;
	}
	return DefendList;
	

}


void Player::issueOrder()
{
	//Returns list of enemy territories that are neighbors that we can attack
	vector<Territory*> AttackList;
	AttackList = toAttack();
	//Returns list of  territories that belong to the player that we can defend
	vector<Territory*> DefendList;
	DefendList = toDefend();

	bool IssueOrder_done = false;
	
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

	int move1 = rand() % AttackList.size();
	int Enemy = AttackList[move1]->getArmyAmount();

	int move2 = rand() % DefendList.size();
	int AdvanceAttack = DefendList[move2]->getArmyAmount();

	if (Enemy >= AdvanceAttack)
	{
		Enemy = Enemy - AdvanceAttack;
		AttackList[move1]->setArmyAmount(Enemy);
		DefendList[move2]->setArmyAmount(0);
	}
	else
	{
		AdvanceAttack = AdvanceAttack - Enemy;
		AttackList[move1]->setArmyAmount(AdvanceAttack);
		DefendList[move2]->setArmyAmount(0);
		AttackList[move1]->setTerritoryOwner(getName());
	}
	//Advance order Defend

	int move3 = rand() % AttackList.size();
	int AdvanceDefend1 = DefendList[move1]->getArmyAmount();

	int move4 = rand() % DefendList.size();
	int AdvanceDefend2 = DefendList[move2]->getArmyAmount();

	if (move3 != move4)
	{
		DefendList[move3]->setArmyAmount(0);
		DefendList[move4]->setArmyAmount(AdvanceDefend1 + AdvanceDefend2);
	}

	//Play card

	//Verify for the Execution of a Special Order

	vector<Card*> Hand = this->getHand()->ShowCards();
	//Monitor if we have already pushed a  Card

	//Play will remove the Card from the player Hand
	string CardType;
	if (handCard.size() != 0) {
		for (Card* c : handCard) {

			CardType = c->GetType();

			if (CardType == "Bomb") {
				//Plays the Card
				c->play(CardType);
				// This breaks out of the loop so we can push one Card at a time
				break;
			}

			if (CardType == "Airlift") {
				c->play(CardType);

				// This breaks out of the loop so we can push one Card at a time
				break;
			}

			if (CardType == "Diplomacy") {
				c->play(CardType);

				// This breaks out of the loop so we can push one Card at a time
				break;
			}

			if (CardType == "Blockade") {
				c->play(CardType);

				// This breaks out of the loop so we can push one Card at a time
				break;
			}

		}
	}
	else {
		cout << "No cards in hand!" << endl;
		
	}

	return;


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





