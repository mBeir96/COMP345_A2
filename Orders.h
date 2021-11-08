#pragma once
#include <vector>
#include <string>
#include <iostream>


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
        virtual void validate();
        virtual void execute() = 0;
        virtual bool getVal();
        virtual const std::string getName() const;
        void setValidate(bool vall);

    private:
        const std::string refName = "";
        const std::string* name;
        bool val;
        

};

class DeployOrders : public Orders
{
    public:
        DeployOrders();
        DeployOrders(bool val);
        DeployOrders(const DeployOrders& d);
        DeployOrders& operator=(const DeployOrders& d);
        friend std::ostream& operator<<(std::ostream &out, const DeployOrders &d);
        friend std::istream& operator>>(std::istream& in, DeployOrders& d);
        ~DeployOrders();
        void validate();
        void execute();
        bool getVal();
        const std::string getName() const;
        void setValidate(bool val);

    private:
        const std::string refName = "Deploy Orders";
        const std::string *name;
        bool val;
};

class AdvanceOrders : public Orders
{
    public:
        AdvanceOrders();    
        AdvanceOrders(bool val);
        AdvanceOrders(const AdvanceOrders& a);
        AdvanceOrders& operator=(const AdvanceOrders& a);
        friend std::ostream& operator<<(std::ostream &out, const AdvanceOrders &a);
        friend std::istream& operator>>(std::istream& in, AdvanceOrders& a);
        ~AdvanceOrders();
        void validate();
        void execute();
        bool getVal();
        const std::string getName() const;
        void setValidate(bool val);

    private:
        const std::string refName = "Advance Orders";
        const std::string *name;
        bool val;

};

class BombOrders : public Orders
{
    public:
        BombOrders();
        BombOrders(bool val);
        BombOrders(const BombOrders& b);
        BombOrders& operator=(const BombOrders& b);
        friend std::ostream& operator<<(std::ostream &out, const BombOrders &a);
        friend std::istream& operator>>(std::istream& in, BombOrders& d);
        ~BombOrders();
        void validate();
        void execute();
        bool getVal();
        const std::string getName() const;
        void setValidate(bool val);

    private:
        const std::string refName = "Bomb Orders";
        const std::string *name;
        bool val;

};

class BlockadeOrders : public Orders
{
    public:
        BlockadeOrders();
        BlockadeOrders(bool val);
        BlockadeOrders(const BlockadeOrders& b);
        BlockadeOrders& operator=(const BlockadeOrders& b);
        friend std::istream& operator>>(std::istream& in, BlockadeOrders& b);
        friend std::ostream& operator<<(std::ostream &out, const BlockadeOrders &b);
        ~BlockadeOrders();
        void validate();
        void execute();
        bool getVal();
        const std::string getName() const;
        void setValidate(bool val);

    private:
        const std::string refName = "Blockade Orders";
        const std::string *name;
        bool val;

};

class AirliftOrders : public Orders
{
    public:
        AirliftOrders();
        AirliftOrders(bool val);
        AirliftOrders(const AirliftOrders& a);
        AirliftOrders& operator=(const AirliftOrders& a);
        friend std::istream& operator>>(std::istream& in, AirliftOrders& a);
        friend std::ostream& operator<<(std::ostream &out, const AirliftOrders &a);
        ~AirliftOrders();
        void validate();
        void execute();
        bool getVal();
        const std::string getName() const;
        void setValidate(bool val);

    private:
        const std::string refName = "Airlift Orders";
        const std::string* name;
        bool val;

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
        void validate();
        void execute();
        bool getVal();
        const std::string getName() const;
        void setValidate(bool val);

    private:
        const std::string refName = "Negotiate Orders";
        const std::string* name;  
        bool val; 
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

