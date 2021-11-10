#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Player.h"


// this is the declaration

class Orders 
{
    public:
        //Orders();
        // Orders(const Orders& o);
        // Orders& operator=(const Orders& o);
        friend std::ostream& operator<<(std::ostream &out, const Orders &o);
        friend std::istream& operator>>(std::istream& in, Orders& o);
        virtual ~Orders();
        virtual bool validate(bool);
        virtual void execute() = 0;
        virtual const std::string getName() const;

    private:
        const std::string refName = "";
        const std::string* name;
        

};

class DeployOrders : public Orders
{
    public:
        DeployOrders();
        DeployOrders(const DeployOrders& d);
        DeployOrders& operator=(const DeployOrders& d);
        friend std::ostream& operator<<(std::ostream &out, const DeployOrders &d);
        friend std::istream& operator>>(std::istream& in, DeployOrders& d);
        ~DeployOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;

    private:
        const std::string refName = "Deploy Orders";
        const std::string *name;
};

class AdvanceOrders : public Orders
{
    public:
        AdvanceOrders();    
        AdvanceOrders(const AdvanceOrders& a);
        AdvanceOrders& operator=(const AdvanceOrders& a);
        friend std::ostream& operator<<(std::ostream &out, const AdvanceOrders &a);
        friend std::istream& operator>>(std::istream& in, AdvanceOrders& a);
        ~AdvanceOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;

    private:
        const std::string refName = "Advance Orders";
        const std::string *name;

};

class BombOrders : public Orders
{
    public:
        BombOrders();
        BombOrders(const BombOrders& b);
        BombOrders& operator=(const BombOrders& b);
        friend std::ostream& operator<<(std::ostream &out, const BombOrders &a);
        friend std::istream& operator>>(std::istream& in, BombOrders& d);
        ~BombOrders();
        bool validate(bool);
        void execute(Player, Player, std::string);
        const std::string getName() const;

    private:
        const std::string refName = "Bomb Orders";
        const std::string *name;

};

class BlockadeOrders : public Orders
{
    public:
        BlockadeOrders();
        BlockadeOrders(const BlockadeOrders& b);
        BlockadeOrders& operator=(const BlockadeOrders& b);
        friend std::istream& operator>>(std::istream& in, BlockadeOrders& b);
        friend std::ostream& operator<<(std::ostream &out, const BlockadeOrders &b);
        ~BlockadeOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;

    private:
        const std::string refName = "Blockade Orders";
        const std::string *name;

};

class AirliftOrders : public Orders
{
    public:
        AirliftOrders();
        AirliftOrders(const AirliftOrders& a);
        AirliftOrders& operator=(const AirliftOrders& a);
        friend std::istream& operator>>(std::istream& in, AirliftOrders& a);
        friend std::ostream& operator<<(std::ostream &out, const AirliftOrders &a);
        ~AirliftOrders();
        bool validate(bool);
        void execute();
        const std::string getName() const;

    private:
        const std::string refName = "Airlift Orders";
        const std::string* name;

};


class NegotiateOrders : public Orders
{
    public:
        NegotiateOrders();
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
};


class OrdersList
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
        std::vector<Orders *>  listOrders;

    private:
    
        
};

