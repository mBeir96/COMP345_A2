#pragma once

#include "LoggingObserver.h"
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

class CommandProcessor;

class ILoggable;
class Observer;


class Command : public Subject, public ILoggable
{
public:
	void saveEffect(CommandProcessor* cp, string effect);

	Command();
	Command(string typed, string effect);
	Command(const Command& old);
	Command& operator = (const Command& t);
	friend std::istream& operator>>(std::istream& in, Command& t);
	friend std::ostream& operator<<(std::ostream& out, const Command& t);
	string typed;
	string effect;

	virtual void stringToLog(string l);

};


class CommandProcessor : public Subject, public ILoggable
{
public:
	CommandProcessor();
	vector<Command*> commands;
	virtual string getCommand(int state);
	bool validate(int state, string command);

	CommandProcessor(const CommandProcessor& old);
	CommandProcessor& operator = (const CommandProcessor& t);
	friend std::istream& operator>>(std::istream& in, CommandProcessor& t);
	friend std::ostream& operator<<(std::ostream& out, const CommandProcessor& t);
	virtual void stringToLog(string l);


protected:
	virtual string readCommand();
	void saveCommand(string toSave);
};

class FileLineReader
{
public:
	FileLineReader();
	FileLineReader(const FileLineReader& old);
	FileLineReader& operator = (const FileLineReader& t);
	friend std::istream& operator>>(std::istream& in, FileLineReader& t);
	friend std::ostream& operator<<(std::ostream& out, const FileLineReader& t);

	string readLineFromFile(ifstream* file);
};

class FileCommandProcessorAdapter : public CommandProcessor, public FileLineReader
{
private:
	
public:
	FileCommandProcessorAdapter();
	FileCommandProcessorAdapter(CommandProcessor* cp);
	FileCommandProcessorAdapter(FileLineReader* flr);

	FileCommandProcessorAdapter(const FileCommandProcessorAdapter& old);
	FileCommandProcessorAdapter& operator = (const FileCommandProcessorAdapter& t);
	friend std::istream& operator>>(std::istream& in, FileCommandProcessorAdapter& t);
	friend std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter& t);

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

