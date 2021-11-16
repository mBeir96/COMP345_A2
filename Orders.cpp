#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include "Player.h"

class Player;
class Territory;
class GameEngine;
//this is the implementation initialisation

void Orders::setSelfPlayers(Player *self){
    this->player = self;
}

void Orders::setTargetTerritory(Territory *target){
    terr = target;
}

Orders& Orders::operator=(const Orders& o)
{
    if (this == &o)
	{
    	return *this;
    }
    this->name = new std::string(*(o.name));

    return *this;
}

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


bool Orders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

const std::string Orders::getName() const
{
    return *name;
}

const Player Orders::getSelfPlayers() const
{
    return *player;
}

const Territory Orders::getTargetTerritory() const
{
    return *terr;
}




//end of the orders class

DeployOrders::DeployOrders()
{
}

DeployOrders::DeployOrders(Player *player, Territory *territory, int numArmy)
{
    player = new Player(*(player));
    terr = new Territory(*(territory));
    numArmy = numArmy;
    this->name = &refName;
    // std::cout << this->val << std::endl;
    // std::cout << *this->name << std::endl;
    // std::cout << this->getVal() << std::endl;
    // std::cout << this->getName() << std::endl;
    
}

DeployOrders::DeployOrders(const DeployOrders &d)
{
    this->player = new Player(*(d.player));
    this->terr = new Territory(*(d.terr));
    this->name = new std::string(*(d.name));
    this->numArmy = d.numArmy;
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

void DeployOrders::setSelfPlayers(Player *self){
    this->player = self;
}

void DeployOrders::setTargetTerritory(Territory *target){
    terr = target;
}

const std::string DeployOrders::getName() const
{
    return "Deploy";
    //return *name;
}

int DeployOrders::getNumArmy()
{
    return numArmy;
}

void DeployOrders::setNumArmy(int number)
{
    numArmy = number;
}


const Player DeployOrders::getSelfPlayers() const
{
    return *player;
}

const Territory DeployOrders::getTargetTerritory() const
{
    return *terr;
}

void DeployOrders::execute()
{

    if(this->terr->getTerritoryOwner() != this->player)
    {
        //If the target territory does not belong to the player that issued the order, the order is invalid.
        this->validate(false);
        return;
    }

    //the selected number of armies is added to the number of armies on that territory.
    this->validate(true);
    player->setReinforcementPool(player->getReinforcementPool() - numArmy);
    terr->army = terr->army + numArmy;


}

bool DeployOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

//end of DeployOrders



AdvanceOrders::AdvanceOrders()
{
    player = nullptr;
    terr;
    name;
}

AdvanceOrders::AdvanceOrders(Player *player, Territory *territory)
{
    player = new Player(*(player));
    terr = new Territory(*(territory));
    this->name = &refName;
}

AdvanceOrders::~AdvanceOrders()
{
    delete name;
    name = nullptr;
}

AdvanceOrders::AdvanceOrders(const AdvanceOrders &a)
{
    this->player = new Player(*(a.player));
    this->terr = new Territory(*(a.terr));
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
    return "Advancing";
    //return *name;
}

void AdvanceOrders::setSourceTerritory(Territory* sourceTerr)
{
    source = sourceTerr;
}

void AdvanceOrders::setArmyUnits(int units)
{
    *(armyUnits) = units;
}

//checks if source and target are adjacent
bool AdvanceOrders::isAdjacent() {
    
    for (int i = 0; i < source->edges.size(); i++)
    {
        if (source->edges.at(i) == terr)
        {
            return true;
        }
    }
    
    return false;
}

int AdvanceOrders::getCasualties(int units, bool attacking) {
    int rand;
    int total;
    int percentage;

    if (attacking)
    {
        percentage = 60;
    }
    else
    {
        percentage = 70;
    }

    for (int i = 0; i < units; i++)
    {
        rand = std::rand() % 100;
        if (rand <= percentage)
        {
            total++;
        }
    }

    return total;
}

const Player AdvanceOrders::getSelfPlayers() const
{
    return *player;
}

const Territory AdvanceOrders::getTargetTerritory() const
{
    return *terr;
}

//en dernier
void AdvanceOrders::execute()
{
    //invalid if not owner of source or adjacent
    if (source->getTerritoryOwner() == player || !isAdjacent()) {
        this->validate(false);
        return;
    }

    //add army units if player owns territory
    if (terr->getTerritoryOwner() == player)
    {
        source->setArmyAmount(source->army - *armyUnits);
        terr->setArmyAmount(terr->getArmyAmount() + *(armyUnits));
        this->validate(true);
        return;
    }

    this->validate(true);
    //attacking portion now
    int playerAttacks = getCasualties(source->army, true);
    int enemyAttacks = getCasualties(terr->army, false);

    //set army counts

    //set player army count
    if (source->army - enemyAttacks <=0)
    {
        source->setArmyAmount(0);
    }
    else
    {
        source->setArmyAmount(source->army - enemyAttacks);
    }

    //set enemy army count
    if (terr->army - playerAttacks <= 0)
    {
        terr->setArmyAmount(0);
    }
    else
    {
        terr->setArmyAmount(terr->army - playerAttacks);
    }

    //transfer terr (target territory) to player
    if (terr->army == 0) {
        //search for territory
        int index = 0;
        for (int i = 0; i < terr->player->getTerritory().size(); i++)
        {
            if (terr == terr->player->getTerritory().at(i))
            {
                index = i;
                break;
            }
        }

        //remove from enemy 
        terr->player->getTerritory().erase(terr->player->getTerritory().begin() + index);
        //change ownership
        terr->setTerritoryOwner(player);
        //give player ownership
        player->getTerritory().push_back(terr);
    }


}

bool AdvanceOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

//end of AdvanceOrders

BombOrders::BombOrders()
{
}

BombOrders::BombOrders(Player *player, Territory *territory)
{
    player = new Player(*(player));
    terr = new Territory(*(territory));
    this->name = &refName;
}

BombOrders::BombOrders(const BombOrders& b)
{
    this->player = new Player(*(b.player));
    this->terr = new Territory(*(b.terr));
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

void BombOrders::setSelfPlayers(Player *self){
    this->player = self;
}

void BombOrders::setTargetTerritory(Territory *target){
    terr = target;
}

const std::string BombOrders::getName() const
{
    return "Bomb";
    //return *name;
}

const Player BombOrders::getSelfPlayers() const
{
    return *player;
}

const Territory BombOrders::getTargetTerritory() const
{
    return *terr;
}

void BombOrders::execute()
{

    if(this->terr->getTerritoryOwner() == this->player)
    {
        //If the target territory does not belong to the player that issued the order, the order is invalid.
        this->validate(false);
        return;
    }

    this->terr->setArmyAmount(this->terr->army / 2);
    
}

bool BombOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

//end BombOrders

BlockadeOrders::BlockadeOrders()
{
}

BlockadeOrders::BlockadeOrders(Player *player, Territory *territory, GameEngine* gm)
{
    player = new Player(*(player));
    terr = new Territory(*(territory));
    gm = gm;

    this->name = &refName;
}

BlockadeOrders::BlockadeOrders(const BlockadeOrders& b)
{
    this->gm = new GameEngine(*(b.gm));
    this->player = new Player(*(b.player));
    this->terr = new Territory(*(b.terr));
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
    return "Blockade";
    //return *name;
}

const Player BlockadeOrders::getSelfPlayers() const
{
    return *player;
}

const Territory BlockadeOrders::getTargetTerritory() const
{
    return *terr;
}

void BlockadeOrders::setSelfPlayers(Player *self){
    this->player = self;
}

void BlockadeOrders::setTargetTerritory(Territory *target){
    terr = target;
}

void BlockadeOrders::execute()
{

    if(this->terr->getTerritoryOwner() != player)
    {
        //If the target territory belongs to an enemy player, the order is declared invalid.
        this->validate(false);
        return;
    }

    terr->army = terr->army * 2;
    //the territory will belong to an neutral player
    for(int i = 0; i < (int) gm->players.size(); i++)
    {
        if(gm->players.at(i)->getName() == "Neutral Player")
        {
            gm->players.at(i)->setTerritory(terr);
            break;
        }
        if(i == (int) gm->players.size() - 2)
        {
            //create a neutral player
            std::cout << "Create a Neutral Player!!!" << std::endl;
            gm->addPlayer();
        }
    }

    for(int i = 0; i < (int) player->getTerritory().size(); i++)
    {
        if(player->getTerritory().at(i) == terr)
        {
            player->getTerritory().at(i) = nullptr;
            break;
        }
    }

    
}

bool BlockadeOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}

//end BlockadeOrders

AirliftOrders::AirliftOrders()
{
}

AirliftOrders::AirliftOrders(Player *player, Territory *source, Territory *target)
{
    player = new Player(*(player));
    source = new Territory(*(source));
    target = new Territory(*(target));
    this->name = &refName;
}

AirliftOrders::AirliftOrders(const AirliftOrders& a)
{
    this->player = new Player(*(a.player));
    this->source = new Territory(*(a.source));
    this->target = new Territory(*(a.target));
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
    return "Airlift";
    //return *name;
}

int AirliftOrders::getNumArmy()
{
    return numArmy;
}

const Player AirliftOrders::getSelfPlayers() const
{
    return *player;
}

const Territory AirliftOrders::getTargetTerritory() const
{
    return *target;
}

const Territory AirliftOrders::getSourceTerritory() const
{
    return *source;
}

void AirliftOrders::setNumArmy(int number)
{
    numArmy = number;
}

void AirliftOrders::setSelfPlayers(Player *self){
    this->player = self;
}

void AirliftOrders::setTargetTerritory(Territory *target){
    this->target = target;
}


void AirliftOrders::setSourceTerritory(Territory *target){
    source = target;
}




void AirliftOrders::execute()
{

    //invalid if source or target not owned by player
    if(this->source->getTerritoryOwner() != player || this->target->getTerritoryOwner() != player)
    {
        //If the target territory belongs to an enemy player, the order is declared invalid.
        this->validate(false);
        return;
    }

    if(this->source->getTerritoryOwner() == player && this->target->getTerritoryOwner() == player)
    {
        // If both the source and target territories belong to the player that issue the airlift order, then the selected
        // number of armies is moved from the source to the target territory.
        this->validate(true);
        source->army = source->army - numArmy;
        target->army += numArmy;
        return;
    }

    /*
    if(this->source->getTerritoryOwner() == player && this->target->getTerritoryOwner() != player)
    {
        // If the target territory does not belong to the player that issued the airlift order, the selected number of
        // armies is attacking that territory (see “advance order”).
        //maybe put it on the hand of player?
        AdvanceOrders *ao = new AdvanceOrders();
        ao->execute();
        delete ao;
        ao = nullptr;
    }
    */
}

bool AirliftOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}


//end AirliftOrders

//keep everything with negotiate orders

NegotiateOrders::NegotiateOrders()
{
}

NegotiateOrders::NegotiateOrders(Player *player, Territory *territory)
{
    player = new Player(*(player));
    terr = new Territory(*(territory));
    this->name = &refName;
}

NegotiateOrders::NegotiateOrders(const NegotiateOrders& n)
{
    this->player = new Player(*(n.player));
    this->terr = new Territory(*(n.terr));
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
    return "Negotiation";
    //return *name;
}

void NegotiateOrders::execute()
{
    //if you negotiate yourself its invalid
    if(terr->getTerritoryOwner() == player)
    {
        this->validate(false);
    }

    //If the target is an enemy player, then the effect is that any attack that may be declared between territories
    //of the player issuing the negotiate order and the target player will result in an invalid order  
    //add truce to both players
    player->addTruce(terr->getTerritoryOwner());
    terr->getTerritoryOwner()->addTruce(player);

    this->validate(true);
}

bool NegotiateOrders::validate(bool valid)
{
    std::cout << this->getName() << ((valid) ? " is valid." : " is not valid.") << std::endl;
    return valid;
}


//end NegotiateOrders


OrdersList::OrdersList()
{
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

void OrdersList::put(Orders* o)
{
    listOrders.push_back(o);
}






