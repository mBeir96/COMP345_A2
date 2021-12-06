#pragma once
#include "Map.h"

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
    vector<Territory*> getNeighbourTerritories(Territory*);
    Hand* getCard();
    void issueOrder();

    string getName();
    int getReinforcementPool(); 
    void setReinforcementPool(int);
    void setOrder(Orders*);
    void setTerritory(Territory*);
    void removeTerritory(int i);
    void setName(string);
    void setHand(Card* c);
    
    void printOrder();
    void printHandcard();
    bool playerContientBouns();
    void addTruce(Player*);
    void removeAllTruces();
    bool hasTruce(Player*);
    vector<Territory*> territory;
    int reinforcementPool;

    void setStrategy(PlayerStrategy* P);

private:
    string name;
    //int reinforcementPool;

   // vector<Territory*> territory;
    Hand* handCard;
    vector<Orders*> orderList;
    vector<Player*> playerTruces;

    //friend classes
    friend class Hand;
    friend class GameEngine;
    friend class Map;
};


