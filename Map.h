#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

//Territory class
class Territory
{
public:

	Territory();
	Territory(string continent, string country, string player, int value, int army, vector<Territory*> edges);
	Territory(const Territory &old);
	Territory& operator = (const Territory &t);
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
	Map(const Map &old);
	~Map();
	void validate();
	vector<Territory>* theMap;
};

//MapLoader class
class MapLoader
{
public:
	vector<Territory>* readMap(string file);
};
