#include <vector>
#include "Orders.h"


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

void Orders::setValidate(bool val)
{
    this->val = new bool(val);
}

void Orders::validate()
{
}

const std::string Orders::getName() const
{
    return *name;
}

bool Orders::getVal()
{

}

//end of the orders class

DeployOrders::DeployOrders()
{
    this->val = new bool;
    this->name = new std::string;
    
}

DeployOrders::DeployOrders(bool val)
{
    this->val = val;
    this->name = &refName;
    // std::cout << this->val << std::endl;
    // std::cout << *this->name << std::endl;
    // std::cout << this->getVal() << std::endl;
    // std::cout << this->getName() << std::endl;
}

DeployOrders::DeployOrders(const DeployOrders &d)
{
    this->val = new bool((d.val));
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
    this->val = new bool((d.val));
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

bool DeployOrders::getVal()
{
    return val;
}

void DeployOrders::setValidate(bool val)
{
    this->val = new bool(val);
}

const std::string DeployOrders::getName() const
{
    return *name;
}

void DeployOrders::execute()
{

}

void DeployOrders::validate()
{
}

//end of DeployOrders



AdvanceOrders::AdvanceOrders()
{
    this->val = new bool;
    this->name = new std::string;
}


AdvanceOrders::AdvanceOrders(bool val)
{ 
    this->val = val;
    this->name = &refName;
}

AdvanceOrders::~AdvanceOrders()
{
    delete name;
    name = nullptr;
}

AdvanceOrders::AdvanceOrders(const AdvanceOrders &a)
{
    val = new bool((a.val));
    name = new std::string(*(a.name));
}

AdvanceOrders& AdvanceOrders::operator=(const AdvanceOrders& a)
{
    if (this == &a)
	{
    	return *this;
    }
    val = new bool((a.val));
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

bool AdvanceOrders::getVal()
{
    return val;
}

void AdvanceOrders::setValidate(bool val)
{
    this->val = new bool(val);
}

const std::string AdvanceOrders::getName() const
{
    return *name;
}

void AdvanceOrders::execute()
{

}

void AdvanceOrders::validate()
{
}

//end of AdvanceOrders


BombOrders::BombOrders()
{
    this->val = new bool;
    this->name = new std::string;
}


BombOrders::BombOrders(bool val)
{
    this->val = val;
    this->name = &refName;
}

BombOrders::BombOrders(const BombOrders& b)
{
    val = new bool((b.val));
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
    val = new bool((b.val));
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

bool BombOrders::getVal()
{
    return val;
}

void BombOrders::setValidate(bool val)
{
    this->val = new bool(val);
}

const std::string BombOrders::getName() const
{
    return *name;
}

void BombOrders::execute(Cards)
{

}

void BombOrders::validate()
{
}

//end BombOrders

BlockadeOrders::BlockadeOrders()
{
    this->val = new bool;
    this->name = new std::string;
}


BlockadeOrders::BlockadeOrders(bool val)
{
    this->val = val;
    this->name = &refName;
}

BlockadeOrders::BlockadeOrders(const BlockadeOrders& b)
{
    val = new bool((b.val));
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
    val = new bool((b.val));
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

bool BlockadeOrders::getVal()
{
    return val;
}

void BlockadeOrders::setValidate(bool val)
{
    this->val = new bool(val);
}

const std::string BlockadeOrders::getName() const
{
    return *name;
}

void BlockadeOrders::execute()
{

}

void BlockadeOrders::validate()
{
}

//end BlockadeOrders

AirliftOrders::AirliftOrders()
{
    this->val = new bool;
    this->name = new std::string;
}

AirliftOrders::AirliftOrders(bool val)
{
    this->val = val;
    this->name = &refName;
}

AirliftOrders::AirliftOrders(const AirliftOrders& a)
{
    val = new bool((a.val));
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
    val = new bool((a.val));
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

bool AirliftOrders::getVal()
{
    return val;
}

void AirliftOrders::setValidate(bool val)
{
    this->val = new bool(val);
}

const std::string AirliftOrders::getName() const
{
    return *name;
}

void AirliftOrders::execute()
{

}

void AirliftOrders::validate()
{
}


//end AirliftOrders

NegotiateOrders::NegotiateOrders()
{
    this->val = new bool;
    this->name = new std::string;
}

NegotiateOrders::NegotiateOrders(bool val)
{
    this->val = val;
    this->name = &refName;
}

NegotiateOrders::NegotiateOrders(const NegotiateOrders& n)
{
    val = new bool((n.val));
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
    val = new bool((n.val));
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

bool NegotiateOrders::getVal()
{
    return val;
}

void NegotiateOrders::setValidate(bool val)
{
    this->val = new bool(val);
}

const std::string NegotiateOrders::getName() const
{
    return *name;
}

void NegotiateOrders::execute()
{

}

void NegotiateOrders::validate()
{
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
    DeployOrders* o1= new DeployOrders(false);
    AdvanceOrders* o2 = new AdvanceOrders(true);
    BombOrders* o3 = new BombOrders(true);
    BlockadeOrders* o4 = new BlockadeOrders(false);
    AirliftOrders* o5 = new AirliftOrders(false);
    NegotiateOrders* o6 = new NegotiateOrders(true);
    NegotiateOrders* o7 = new NegotiateOrders(true);
    DeployOrders* o8 = new DeployOrders(true);
    AirliftOrders* o9 = new AirliftOrders(false);
    DeployOrders* o10 = new DeployOrders(false);
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

OrdersList& OrdersList::operator=(const OrdersList& n)
{
    listOrders = n.listOrders;

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





