#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "LoggingObserver.h"
#include "Player.h"
#include "GameEngine.h"
#include "Map.h"


class Player;
class GameEngine;
class Territory;


// this is the declaration

class Orders : public Subject, public ILoggable
{
    public:
        //Orders();
        // Orders(const Orders& o);
        Orders& operator=(const Orders& o);
        friend std::ostream& operator<<(std::ostream &out, const Orders &o);
        friend std::istream& operator>>(std::istream& in, Orders& o);
        virtual ~Orders();
        virtual bool validate(bool);
        virtual void execute() = 0;
        virtual const std::string getName() const;
        virtual void setSelfPlayers(Player *self);
        virtual void setTargetTerritory(Territory* terr);
        virtual const Player getSelfPlayers() const;
        virtual const Territory getTargetTerritory() const;



        virtual void stringToLog(string l);
        



    private:
        const std::string refName = "";
        const std::string* name;
        Player* player;
        Territory* terr;

};

class DeployOrders : public Orders
{
    public:
        DeployOrders();
        DeployOrders(Player* player, Territory* territory, int numArmy);
        DeployOrders(const DeployOrders& d);
        DeployOrders& operator=(const DeployOrders& d);
        friend std::ostream& operator<<(std::ostream &out, const DeployOrders &d);
        friend std::istream& operator>>(std::istream& in, DeployOrders& d);
        ~DeployOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;
        void setSelfPlayers(Player *self);
        void setTargetTerritory(Territory* terr);
        int getNumArmy();
        void setNumArmy(int number);
        const Player getSelfPlayers() const;
        const Territory getTargetTerritory() const;

    private:
        const std::string refName = "Deploy Orders";
        const std::string *name;
        Player* player;
        Territory* terr;
        int numArmy;
};

//keep this the same
class AdvanceOrders : public Orders
{
    public:
        AdvanceOrders();
        AdvanceOrders(Player* player, Territory* territory);    
        AdvanceOrders(const AdvanceOrders& a);
        AdvanceOrders& operator=(const AdvanceOrders& a);
        friend std::ostream& operator<<(std::ostream &out, const AdvanceOrders &a);
        friend std::istream& operator>>(std::istream& in, AdvanceOrders& a);
        ~AdvanceOrders();
        bool validate(bool);
        void execute();
        void execute(Player self, Player enemy, std::string source, std::string target, int numArmy, Territory edges);
        const std::string getName() const;
        void setSourceTerritory(Territory*);
        void setArmyUnits(int units);
        bool isAdjacent();
        int getCasualties(int army, bool isAttacking);
        const Player getSelfPlayers() const;
        const Territory getTargetTerritory() const;

    private:
        const std::string refName = "Advance Orders";
        const std::string *name;
        Player* player;
        Territory* terr;
        Territory* source;
        int* armyUnits;

};

class BombOrders : public Orders
{
    public:
        BombOrders();
        BombOrders(Player* player, Territory* territory);
        BombOrders(const BombOrders& b);
        BombOrders& operator=(const BombOrders& b);
        friend std::ostream& operator<<(std::ostream &out, const BombOrders &a);
        friend std::istream& operator>>(std::istream& in, BombOrders& d);
        ~BombOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;
        void setSelfPlayers(Player *self);
        void setTargetTerritory(Territory* terr);
        const Player getSelfPlayers() const;
        const Territory getTargetTerritory() const;

    private:
        const std::string refName = "Bomb Orders";
        const std::string *name;
        Player* player;
        Territory* terr;

};

class BlockadeOrders : public Orders
{
    public:
        BlockadeOrders();
        BlockadeOrders(Player* player, Territory* territory, GameEngine *gm);
        BlockadeOrders(const BlockadeOrders& b);
        BlockadeOrders& operator=(const BlockadeOrders& b);
        friend std::istream& operator>>(std::istream& in, BlockadeOrders& b);
        friend std::ostream& operator<<(std::ostream &out, const BlockadeOrders &b);
        ~BlockadeOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;
        void setSelfPlayers(Player *self);
        void setTargetTerritory(Territory* terr);
        const Player getSelfPlayers() const;
        const Territory getTargetTerritory() const;
        GameEngine *gm;

    private:
        const std::string refName = "Blockade Orders";
        const std::string *name;
        Player* player;
        Territory* terr;

};

class AirliftOrders : public Orders
{
    public:
        AirliftOrders();
        AirliftOrders(Player* player, Territory* source, Territory* target);
        AirliftOrders(const AirliftOrders& a);
        AirliftOrders& operator=(const AirliftOrders& a);
        friend std::istream& operator>>(std::istream& in, AirliftOrders& a);
        friend std::ostream& operator<<(std::ostream &out, const AirliftOrders &a);
        ~AirliftOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;
        void setSelfPlayers(Player *self);
        void setTargetTerritory(Territory* terr);
        void setSourceTerritory(Territory* terr);
        const Player getSelfPlayers() const;
        const Territory getTargetTerritory() const;
        const Territory getSourceTerritory() const;
        int getNumArmy();
        void setNumArmy(int number);

    private:
        const std::string refName = "Airlift Orders";
        const std::string* name;
        Player* player;
        Territory* source;
        Territory* target;
        int numArmy;

};


//keep this the same
class NegotiateOrders : public Orders
{
    public:
        NegotiateOrders();
        NegotiateOrders(Player* player, Territory* territory);
        NegotiateOrders(bool val);
        NegotiateOrders(const NegotiateOrders& n);
        NegotiateOrders& operator=(const NegotiateOrders& n);
        friend std::istream& operator>>(std::istream& in, NegotiateOrders& n);
        friend std::ostream& operator<<(std::ostream &out, const NegotiateOrders &n);
        ~NegotiateOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;


    private:
        const std::string refName = "Negotiate Orders";
        const std::string* name; 
        Player* player;
        Territory* terr; 
};


class OrdersList : public Subject, public ILoggable
{
    public:
        OrdersList();
        OrdersList(const OrdersList& o);
        OrdersList& operator=(const OrdersList& o);
        friend std::istream& operator>>(std::istream& in, OrdersList& o);
        friend std::ostream& operator<<(std::ostream &out, const OrdersList &o);
        ~OrdersList();
        void remove(int index);
        void move(int firstIndex, int secondIndex);
        void put(Orders* o);
        std::vector<Orders *>  listOrders;


        virtual void stringToLog(string l);


    private:
    
        
};

