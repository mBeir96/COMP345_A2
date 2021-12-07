#pragma once
#include "Map.h"
#include "PlayerStrategy.h";
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Hand;
class Orders;
class Territory;
class Card;
class PlayerStrategy;
enum PlayerType;
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
    void removeTerritory(int i);
    void removeAllTerritories();
    void setName(string);
    void setHand(Card* c);
    
    void printOrder();
    void printHandcard();
    bool playerContientBouns();
    void addTruce(Player*);
    void removeAllTruces();
    bool hasTruce(Player*);
    void setPlayerStrategy(PlayerType type);
    void printStrategy();
    void removePlayerStrategy();

    //These are needed for human interaction
    void setMap(vector<Territory*> map);
    void setNeutralPlayer(Player* neutralPlayer);

    vector<Territory*> getMap();
    Player* getNeutralPlayer();

private:
    string name;
    int reinforcementPool;
    PlayerStrategy* strategy;
    vector<Territory*> territory;
    Hand* handCard;
    vector<Orders*> orderList;
    vector<Player*> playerTruces;

    vector<Territory*> map;
    Player* neutralPlayer;

    //friend classes
    friend class Hand;
    friend class GameEngine;
    friend class Map;
};


