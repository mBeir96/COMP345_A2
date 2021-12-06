#pragma once
#include "Player.h"
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

class Player;
//all class need to have an assignment operator, and stream insertion operator.
//Territory class
class Territory
{
public:

	Territory();
	Territory(string continent, string country, Player* player, int value, int army, vector<Territory*> edges);
	Territory(const Territory &old);
	Territory& operator = (const Territory &t);
	friend std::istream& operator>>(std::istream& in, Territory& t);
    friend std::ostream& operator<<(std::ostream &out, const Territory &t);
	~Territory();
	string continent;
	string country;
	Player *player; //replace with actual player
	int value;
	int army;
	Player* owner;// add for part 1 of A3
	vector<Territory*> edges;

	//accessors for private values
	string getTname();
	string getContinent();
	Player* getTerritoryOwner();
	int getArmyAmount();
	//mutator for priv values
	void setTname(string n);
	void setContinent(string n);
	void setTerritoryOwner(Player* p);
	void setArmyAmount(int n);
};

//Map class
class Map
{
public:
	Map();
	Map(vector<Territory>* map);
	Map& operator = (const Map& m);
	friend std::istream& operator>>(std::istream& in, Map& m);
    friend std::ostream& operator<<(std::ostream &out, const Map &m);
	Map(const Map &old);
	~Map();
	bool validate();
	vector<Territory>* theMap;



};

//MapLoader class
class MapLoader
{
public:
	MapLoader& operator = (const MapLoader& m);
	friend std::istream& operator>>(std::istream& in, MapLoader& m);
    friend std::ostream& operator<<(std::ostream &out, const MapLoader &m);
	vector<Territory>* readMap(string file);
};
