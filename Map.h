#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

//all class need to have an assignment operator, and stream insertion operator.
//Territory class
class Territory
{
public:

	Territory();
	Territory(string continent, string country, string player, int value, int army, vector<Territory*> edges);
	Territory(const Territory &old);
	Territory& operator = (const Territory &t);
	friend std::istream& operator>>(std::istream& in, Territory& t);
    friend std::ostream& operator<<(std::ostream &out, const Territory &t);
	~Territory();
	string continent;
	string country;
	string *player; //replace with actual player
	int value;
	int army;
	vector<Territory*> edges;
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
	void validate();
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
