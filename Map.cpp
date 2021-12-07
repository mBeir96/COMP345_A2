#pragma once
#include "Map.h"


//Territory class

//default constructor
Territory::Territory()
{
	continent = "";
	country = "";
	player = nullptr;
	value = 0;
	army = 0;
	edges;
}

//parameterized constructor
Territory::Territory(string cont, string coun, Player* pl, int val, int ar, vector<Territory*> ed)
{
	continent = cont;
	country = coun;
	player = pl;
	value = val;
	army = ar;
	edges = ed;
}

//copy constructor
Territory::Territory(const Territory& old)
{
	continent = old.continent;
	country = old.country;
	player = old.player;
	value = old.value;
	army = old.army;
	edges = old.edges;
}

//assignment operator
Territory& Territory::operator=(const Territory& t)
{
    if (this == &t)
	{
    	return *this;
    }
    army = t.army;
	continent = t.continent;
	country = t.country;
	value = t.value;
	player = t.player;
	edges = t.edges;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Territory& t)
{
    out << t.army << t.continent << t.country << t.player << t.value << t.edges.at(0);
    return out;
}

std::istream& operator>>(std::istream& in, Territory& t)
{
    return in;
}

//destructor
Territory::~Territory()
{
	if (player != NULL)
	{
		delete player;
		player = NULL;
	}
	
	
}

string Territory::getTname()
{
	return country;
}

string Territory::getContinent()
{
	return continent;
}

Player* Territory::getTerritoryOwner()
{
	return player;
}

int Territory::getArmyAmount()
{
	return army;
}

//mutator for priv values
void Territory::setTname(string n)
{
	country = n;
}
void Territory::setContinent(string n)
{
	continent = n;
}

void Territory::setTerritoryOwner(Player* p)
{
	player = p;
}

void Territory::setArmyAmount(int n)
{
	army = n;
}



//Map class

//default constructor
Map::Map()
{
	theMap = NULL;
}

//parameterized constructor
Map::Map(vector<Territory>* x)
{
    theMap = x;
}

//copy constructor
Map::Map(const Map &old)
{
	theMap = old.theMap;
}

//assignemnt operator
Map& Map::operator=(const Map& m)
{
    if (this == &m)
	{
    	return *this;
    }
    this->theMap = m.theMap;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Map& m)
{
    out << m.theMap->at(0);
    return out;
}

std::istream& operator>>(std::istream& in, Map& m)
{
    return in;
}

//destructor
Map::~Map()
{
    delete theMap;
	theMap = NULL;
}



//validate method
bool Map::validate()
{
	if (theMap->size() == 0)
	{
		return false;
	}
	//showing that theMap is a connected graph
	//cout << "\nThe following is the relations between each country: \n";
	
	/*for (int i = 0; i < theMap->size(); i++)
	{
		cout << theMap->at(i).country << " (";
		for (int j = 0; j < theMap->at(i).edges.size(); j++)
		{
			cout << theMap->at(i).edges.at(j)->country << ", ";
		}
		cout << ")\n";
	}*/
	//system("pause");
	//showing that the contienets are a subgraph
	//cout << "\nThe following is to prove the continental subgraph: \n";
	
	/*for (int j = 0; j < theMap->size(); j++)
	{
		for (int k = 0; k < theMap->at(j).edges.size(); k++)
		if (theMap->at(j).continent != theMap->at(j).edges.at(k)->continent)
		{
			cout << "Can access " << theMap->at(j).continent << " from " << theMap->at(j).edges.at(k)->continent <<
				" by " << theMap->at(j).country << " and " << theMap->at(j).edges.at(k)->country << "\n";
		}
	}*/
	//system("pause");
	//showing that the countries belong to one and only one continent
	//cout << "\nThe following is to prove that every country belongs to one and only one continent\n";

	/*for (int i = 0; i < theMap->size(); i++)
	{
		cout << theMap->at(i).country << " belongs to " << theMap->at(i).continent << "\n";
	}
	*/
	return true;
}

//MapLoader constructor and operator
MapLoader& MapLoader::operator=(const MapLoader& m)
{
    if (this == &m)
	{
    	return *this;
    }

    return *this;
}

std::ostream& operator<<(std::ostream& out, const MapLoader& m)
{

    return out;
}

std::istream& operator>>(std::istream& in, MapLoader& m)
{
    return in;
}

//MapLOader class
vector<Territory>* MapLoader::readMap(string file_name)
{
	vector<Territory>* territories = new vector<Territory>;
	
	int count = 0;

	ifstream inFile(file_name.c_str());

	if (!inFile)
	{
		cerr << "unable to open input file: " << file_name << " ending program!\n";
		return territories;
	}

	string next;
	vector<string> continent;
	vector<string> words;
	vector<int> nbrs;

	//getting to the part that names the continents
	while (next != "[continents]")
	{
		std::getline(inFile, next);
		//adding a count to break the loop if [continents] is never found
		count++;
		if (count > 30)
			break;
	}

	//resetting count for future use
	count = 0;

	//storing coontinents in vector continents
	if (next == "[continents]")
	{
		while (next != "")
		{
			std::getline(inFile, next);
			if (next != "")
			{
				next = next.substr(0, next.find(' '));
				// making sure the first value is not an int
				if (!isdigit(next.at(0)))
				{
					continent.push_back(next);
				}
				else
				{
					cout << "the first value of a continent should be the continent's name please check the file and try again";
					return NULL;
				}
			}
		}
	}
	//returning an empty pointer because file had an invalid continent section
	if (continent.empty())
	{
		cout << "File had an invalid [continents] section. Please check the formatting and try again";
		return NULL;
	}
	/*for (int i = 0; i < continent.size(); i++)
	{
		cout << i << " " << continent.at(i) << "\n";
	}*/

	//getting to the part that names the countries
	while (next != "[countries]")
	{
		std::getline(inFile, next);
		//adding a count to break the loop if [countries] is never found
		count++;
		if (count > 30)
			break;
	}

	//resetting count value for future use
	count = 0;

	//storing the values of the territories
	if (next == "[countries]")
	{		while (next != "")
			{
				Territory empty;
				std::getline(inFile, next);
				if (next != "" && next.length() < 50)
				{
					size_t pos = 0;
					string space = " ";
					//seperating the words by spaces
					while ((pos = next.find(space)) != string::npos)
					{
						words.push_back(next.substr(0, pos));
						next.erase(0, pos + space.length());
					}

					
					//storing the numerical value of the territory into the vector of Territories
					//if it is a number
					if (isdigit(words.at(0).at(0)))
					{
						empty.value = std::stoi(words.at(0));
					}
					else
					{
						cout << "invalid coutries section. The first value on each line should be the country's number";
						return NULL;
					}
					//storing the name of the country into the vector of Territories
					empty.country = words.at(1);
					//storing the name of the continent it belongs to into the vector of Territories
					//if it is a number
					if (isdigit(words.at(2).at(0)))
					{
						empty.continent = continent.at(std::stoi(words.at(2)) - 1);
					}
					else
					{
						cout << "invalid coutries section. The third value on each line should be the country's continent";
						return NULL;
					}
					//erasing previous values for vector words
					words.erase(words.begin(), words.end());
					territories->push_back(empty);
					empty.player = new Player;
					count++;
				}

			}
	}
	//reset value of count
	count = 0;

	//returning an empty pointer because file had an invalid country section
	if (territories->empty())
	{
		cout << "File had an invalid [countries] section. Please check the formatting and try again";
		return NULL;
	}

	//getting to the part that names the borders
	while (next != "[borders]")
	{
		std::getline(inFile, next);
		//adding a count to break the loop if [borders] is never found
		count++;
		if (count > 30)
			break;
	}
	//resseting the count for future use
	count = 0;

	//storing the values of the borders
	if (next == "[borders]")
	{
		while (next != "")
		{
			std::getline(inFile, next);

			if (next != "" && next.length() < 50)
			{
				stringstream ss;
				ss << next;
				string temp;
				int found;
				//seperating the numbers that represent the bordering countries
				while (!ss.eof())
				{
					ss >> temp;
					if (stringstream(temp) >> found)
					{
						nbrs.push_back(found);
					}
					temp = "";
				}
				//creating an vector of Territory pointers to put into the edges of Territories
				vector<Territory*> edges;
				//putting the edges into the edges vector
				for (int i = 1; i < nbrs.size(); i++)
				{
					edges.push_back(&(territories->at((nbrs.at(i) - 1))));
				}
				//putting the edges vector as the Territory's edges value
				if (count <= territories->size())
				{
					territories->at(count).edges = edges;
				}

				//erasing previous values for vector words
				nbrs.erase(nbrs.begin(), nbrs.end());

				//increasing count
				count++;
			}
		}
	}
	//returning an empty pointer because file had an invalid borders section
	//no territory can have no borders so checking the first element should work enough
	if (territories->at(0).edges.empty())
	{
		cout << "File had an invalid [borders] section. Please check the formatting and try again";
		return NULL;
	}
	inFile.close();
	return territories;
}


