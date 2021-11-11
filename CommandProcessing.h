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
	void saveEffect(CommandProcessor* cp, string effect);
public:
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
	virtual void getCommand();
	bool validate(string command);

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
	CommandProcessor* cp;
	FileLineReader* flr;
public:
	FileCommandProcessorAdapter(CommandProcessor* cp);
	FileCommandProcessorAdapter(FileLineReader* flr);
	
	void getCommand(ifstream* file);
	string readCommand(ifstream* file);
};

class CommandProcessing
{
};

