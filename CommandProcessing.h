#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

class CommandProcessor;
class Command
{
public:
	void saveEffect(CommandProcessor* cp, string effect);

	Command();
	Command(string typed, string effect);
	string typed;
	string effect;
};


class CommandProcessor
{
public:
	CommandProcessor();
	vector<Command*> commands;
	virtual string getCommand(int state);
	bool validate(int state, string command);

protected:
	virtual string readCommand();
	void saveCommand(string toSave);
};

class FileLineReader
{
public:
	string readLineFromFile(ifstream* file);
};

class FileCommandProcessorAdapter : public CommandProcessor, public FileLineReader
{
private:
	
public:
	FileCommandProcessorAdapter();
	FileCommandProcessorAdapter(CommandProcessor* cp);
	FileCommandProcessorAdapter(FileLineReader* flr);
	CommandProcessor* cp;
	FileLineReader* flr;
	string getCommand(int state);
	string getCommand(int state, ifstream* file);
	string readCommand();
	string readCommand(ifstream* file);
};

class CommandProcessing
{
};

