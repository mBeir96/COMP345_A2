#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include "Player.h"


//this is the implementation initialisation


// Orders::Orders()
// {
//     //this->val = new bool;
// }

// Orders::Orders(const Orders& o)
// {
//     // val = new bool(o.val);
//     // name = new std::string(*(o.name));
// }

// Orders& Orders::operator=(const Orders& o)
// {
//     // if (this == &o)
// 	// {
//     // 	return *this;
//     // }
//     // this->val = new bool((o.val));
//     // this->name = new std::string(*(o.name));

//     // return *this;
// }

std::ostream& operator<<(std::ostream& out, const Orders& o)
{
    out << o.name;
    return out;
}

std::istream& operator>>(std::istream& in, Orders& o)
{
    return in;
}

Orders::~Orders()
{
    delete name;
    name = nullptr;
}

// bool Orders::getVal()
// {
//     return val;
// }


bool Orders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

const std::string Orders::getName() const
{
    return *name;
}


//end of the orders class

DeployOrders::DeployOrders()
{
    this->name = &refName;
    // std::cout << this->val << std::endl;
    // std::cout << *this->name << std::endl;
    // std::cout << this->getVal() << std::endl;
    // std::cout << this->getName() << std::endl;
    
}

DeployOrders::DeployOrders(const DeployOrders &d)
{
    this->name = new std::string(*(d.name));
}

DeployOrders::~DeployOrders()
{
    delete name;
    name = nullptr;
}


DeployOrders& DeployOrders::operator=(const DeployOrders& d)
{
    if (this == &d)
	{
    	return *this;
    }
    this->name = new std::string(*(d.name));

    return *this;
}

std::ostream& operator<<(std::ostream& out, const DeployOrders& d)
{
    out << d.name;
    return out;
}

std::istream& operator>>(std::istream& in, DeployOrders& d)
{
    return in;
}

const std::string DeployOrders::getName() const
{
    return *name;
}

void DeployOrders::execute()
{

}

bool DeployOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

//end of DeployOrders



AdvanceOrders::AdvanceOrders()
{
    this->name = &refName;
}

AdvanceOrders::~AdvanceOrders()
{
    delete name;
    name = nullptr;
}

AdvanceOrders::AdvanceOrders(const AdvanceOrders &a)
{
    name = new std::string(*(a.name));
}

AdvanceOrders& AdvanceOrders::operator=(const AdvanceOrders& a)
{
    if (this == &a)
	{
    	return *this;
    }
    name = new std::string(*(a.name));

    return *this;
}

std::ostream& operator<<(std::ostream& out, const AdvanceOrders& a)
{
    out << a.name;
    return out;
}

std::istream& operator>>(std::istream& in, AdvanceOrders& a)
{
    return in;
}

const std::string AdvanceOrders::getName() const
{
    return *name;
}

void AdvanceOrders::execute()
{

}

bool AdvanceOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

//end of AdvanceOrders


BombOrders::BombOrders()
{
    this->name = &refName;
}

BombOrders::BombOrders(const BombOrders& b)
{
    name = new std::string(*(b.name));
}

BombOrders::~BombOrders()
{
    delete name;
    name = nullptr;
}

BombOrders& BombOrders::operator=(const BombOrders& b)
{
    if (this == &b)
	{
    	return *this;
    }
    
    name = new std::string(*(b.name));

    return *this;
}

std::ostream& operator<<(std::ostream& out, const BombOrders& b)
{
    out << b.name;
    return out;
}

std::istream& operator>>(std::istream& in, BombOrders& b)
{
    return in;
}

const std::string BombOrders::getName() const
{
    return *name;
}

void BombOrders::execute(Player self, Player enenemy, std::string target)
{
    if(enenemy == self)
    {
      this->validate(false);
      return;                                                          
    }
    for(int i = 0; i < (int)enenemy.getTerritory().size(); i++)
    {
        if(enenemy.getTerritory().at(i)->country == target)
        {
            enenemy.getTerritory().at(i)->army = enenemy.getTerritory().at(i)->army / 2;
        }
    }      
}

bool BombOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

//end BombOrders

BlockadeOrders::BlockadeOrders()
{
    this->name = &refName;
}

BlockadeOrders::BlockadeOrders(const BlockadeOrders& b)
{
    name = new std::string(*(b.name));
}

BlockadeOrders::~BlockadeOrders()
{
    delete name;
    name = nullptr;
}

BlockadeOrders& BlockadeOrders::operator=(const BlockadeOrders& b)
{
    if (this == &b)
	{
    	return *this;
    }
    name = new std::string(*(b.name));

    return *this;
}

std::ostream& operator<<(std::ostream& out, const BlockadeOrders& b)
{
    out << b.name;
    return out;
}

std::istream& operator>>(std::istream& in, BlockadeOrders& b)
{
    return in;
}

const std::string BlockadeOrders::getName() const
{
    return *name;
}

void BlockadeOrders::execute()
{

}

bool BlockadeOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

//end BlockadeOrders

AirliftOrders::AirliftOrders()
{
    this->name = &refName;
}

AirliftOrders::AirliftOrders(const AirliftOrders& a)
{
    name = new std::string(*(a.name));
}

AirliftOrders::~AirliftOrders()
{
    delete name;
    name = nullptr;
}

AirliftOrders& AirliftOrders::operator=(const AirliftOrders& a)
{
    if (this == &a)
	{
    	return *this;
    }
    name = new std::string(*(a.name));

    return *this;
}

std::ostream& operator<<(std::ostream& out, const AirliftOrders& a)
{
    out << a.name;
    return out;
}

std::istream& operator>>(std::istream& in, AirliftOrders& a)
{
    return in;
}

const std::string AirliftOrders::getName() const
{
    return *name;
}

void AirliftOrders::execute()
{

}

bool AirliftOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}


//end AirliftOrders

NegotiateOrders::NegotiateOrders()
{
    this->name = &refName;
}

NegotiateOrders::NegotiateOrders(const NegotiateOrders& n)
{
    name = new std::string(*(n.name));
}

NegotiateOrders::~NegotiateOrders()
{
    delete name;
    name = nullptr;
}

NegotiateOrders& NegotiateOrders::operator=(const NegotiateOrders& n)
{
    if (this == &n)
	{
    	return *this;
    }
    name = new std::string(*(n.name));

    return *this;
}

std::ostream& operator<<(std::ostream& out, const NegotiateOrders& n)
{
    out << n.name;
    return out;
}

std::istream& operator>>(std::istream& in, NegotiateOrders& n)
{
    return in;
}

const std::string NegotiateOrders::getName() const
{
    return *name;
}

void NegotiateOrders::execute()
{

}

bool NegotiateOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}


//end NegotiateOrders


OrdersList::OrdersList()
{
    // if(cardtype == bomb){
    //     listOrders.push_back(new BombOrders(true));
    // }else if(cardtype == reinforcement){
    //     listOrders.push_back(new DeployOrders(false));
    // }else if(cardtype == blockade){
    //     listOrders.push_back(new BlockadeOrders(false));
    // }else if(cardtype == airlift){
    //     listOrders.push_back(new AirliftOrders(false));
    // }else if(cardtype == diplomacy){
    //     listOrders.push_back(new NegotiateOrders(true));
    // }
    //the first parametre is validation;
    DeployOrders* o1= new DeployOrders();
    AdvanceOrders* o2 = new AdvanceOrders();
    BombOrders* o3 = new BombOrders();
    BlockadeOrders* o4 = new BlockadeOrders();
    AirliftOrders* o5 = new AirliftOrders();
    NegotiateOrders* o6 = new NegotiateOrders();
    NegotiateOrders* o7 = new NegotiateOrders();
    DeployOrders* o8 = new DeployOrders();
    AirliftOrders* o9 = new AirliftOrders();
    DeployOrders* o10 = new DeployOrders();
    listOrders.push_back(o1);
    listOrders.push_back(o2);
    listOrders.push_back(o3);
    listOrders.push_back(o4);
    listOrders.push_back(o5);
    listOrders.push_back(o6);
    listOrders.push_back(o7);
    listOrders.push_back(o8);
    listOrders.push_back(o9);
    listOrders.push_back(o10);
}

OrdersList::OrdersList(const OrdersList& o)
{
    this->listOrders = o.listOrders;
}

OrdersList& OrdersList::operator=(const OrdersList& ol)
{
    if (this == &ol)
	{
    	return *this;
    }
    listOrders = ol.listOrders;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const OrdersList& o)
{
    return out;
}

std::istream& operator>>(std::istream& in, OrdersList& o)
{
    return in;
}

OrdersList::~OrdersList()
{
    
}

void OrdersList::move(int firstIndex, int secondIndex)
{
    std::iter_swap(listOrders.begin() + (firstIndex - 1), listOrders.begin() + (secondIndex - 1));
    std::cout << "You move the orders." << std::endl;
}

void OrdersList::remove(int index)
{
    std::cout << "You remove the orders " << listOrders.at(index - 1)->getName() << std::endl;
    listOrders.erase(listOrders.begin() + (index - 1));
}





