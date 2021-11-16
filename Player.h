#pragma once
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include "Player.h"

#include "GameEngine.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Hand;
class Orders;
class Territory;
class Card;
//all class need to have an assignment operator, and stream insertion operator.
class Player {

public:
    Player();       // Default constructor
    Player(string); //added
    Player(int, string, vector<Territory*> territories, Hand* handCard, vector<Orders*> order); //Constructor
    Player(const Player& p); //Copy constructor
    Player& operator = (const Player&); //added
    friend std::istream& operator>>(std::istream& in, Player& p);
    friend std::ostream& operator<<(std::ostream &out, const Player &p);
    bool operator == (const Player&);
    bool operator != (const Player&);
    ~Player(); //Destructor

    //Methods
    vector<Territory*> getTerritory();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    vector<Orders*> getOrderList();
    Hand* getCard();
    void issueOrder();

    string getName();
    int getReinforcementPool(); 
    void setReinforcementPool(int);
    void setOrder(Orders*);
    void setTerritory(Territory*);
    void setName(string);
    void setHand(Card* c);
    
    void printOrder();
    void printHandcard();
    bool playerContientBouns();
    void addTruce(Player*);
    void removeAllTruces();
    bool hasTruce(Player*);

private:
    string name;
    int reinforcementPool;

    vector<Territory*> territory;
    Hand* handCard;
    vector<Orders*> orderList;
    vector<Player*> playerTruces;

    //friend classes
    friend class Hand;
    friend class GameEngine;
    friend class Map;
};


