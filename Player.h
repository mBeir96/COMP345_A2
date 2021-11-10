#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include "GameEngine.h"
using namespace std;
class Territory;
//all class need to have an assignment operator, and stream insertion operator.
class Player {

public:
    Player();       // Default constructor
    Player(string); //added
    Player(int, string, vector<Territory*> territories, vector<Card*> handCard, vector<Orders*> order); //Constructor
    Player(const Player& p); //Copy constructor
    Player& operator = (const Player&); //added
    ~Player(); //Destructor

    //Methods
    vector<Territory*> getTerritory();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    vector<Orders*> getOrderList();
    vector<Card*> getCard();
    void issueOrder();

    string getName();
    int getReinforcementPool();
    void setReinforcementPool(int);
    void setOrder(Orders*);
    void setTerritory(Territory);
    void setName(string);
    
    void printOrder();
    void printHandcard();
    bool playerContientBouns();

private:
    string name;
    int reinforcementPool;

    vector<Territory*> territory;
    vector<Card*> handCard;
    vector<Orders*> orderList;

    //friend classes
    friend class Card;
    friend class GameEngine;
    friend class Map;
};


