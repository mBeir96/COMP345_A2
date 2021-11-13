#include "CommandProcessing.h"
#include "gameEngine.h"

//Command class
Command::Command()
{

}

Command::Command(string typed, string effect)
{
	this->typed = typed;
	this->effect = effect;
}

void Command::saveEffect(CommandProcessor* cp, string effect)
{
	cp->commands.back()->effect = effect;
}

//CommandProcessor class
CommandProcessor::CommandProcessor()
{

}

string CommandProcessor::getCommand(int state)
{
	string enteredCommand = readCommand();
	if (validate(state, enteredCommand))
	{
		saveCommand(enteredCommand);
		return enteredCommand;
	}
	else
		cout << "invalid command at this state";
	return "";
	
};

string CommandProcessor::readCommand()
{
	string command;
	cin >> command;
	return command;
}

void CommandProcessor::saveCommand(string toSave)
{
	Command* command = new Command(toSave, "");
	commands.push_back(command);
}

bool CommandProcessor::validate(int state, string command)
{
	// checking if each command is in the right state
	if (command == "loadmap" && (state == 0 || state == 1))
		return true;
	if (command == "validatemap" && state == 1)
		return true;
	if (command == "addplayer" && (state == 2 || state == 3))
		return true;
	if (command == "gamestart" && state == 3)
		return true;
	if (command == "replay" && state == 7)
		return true;
	if (command == "quit" && state == 7)
		return true;
	return false;
}

// FileCommandProcessorAdapter Class
FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
	cp = NULL;
	flr = NULL;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(CommandProcessor* cp)
{
	this->cp = cp;
	flr = NULL;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* flr)
{
	cp = NULL;
	this->flr = flr;
}

string FileCommandProcessorAdapter::getCommand(int state)
{
	string enteredCommand = readCommand();
	if (validate(state, enteredCommand))
	{
		saveCommand(enteredCommand);
		return enteredCommand;
	}
	else
		cout << "invalid command at this state";
	return "";
}

string FileCommandProcessorAdapter::getCommand(int state, ifstream* file)
{
	string enteredCommand = readCommand(file);
	if (validate(state, enteredCommand))
	{
		saveCommand(enteredCommand);
		return enteredCommand;
	}
	else
		cout << "invalid command at this state";
	return "";
}

string FileCommandProcessorAdapter::readCommand()
{
	string command;

	cin >> command;

	return command;
}

string FileCommandProcessorAdapter::readCommand(ifstream* file)
{
	string command = flr->readLineFromFile(file);
	return command;
}



// FileLineReader Class
string FileLineReader::readLineFromFile(ifstream* file)
{
	string next;
	string word;
	if (!file->eof())
	{
		next = file->get();
	}
	
	while (next != " " && next != "\n" && !file->eof())
	{
		word = word + next;
		next = file->get();
	}
	
	return word;
}