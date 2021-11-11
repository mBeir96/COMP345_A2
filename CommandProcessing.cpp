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

void CommandProcessor::getCommand()
{
	string enteredCommand = readCommand();
	if (validate(enteredCommand))
	{
		saveCommand(enteredCommand);
	}
	
};

string CommandProcessor::readCommand()
{
	string command;
	cout << "\nPlease enter a command: ";
	cin >> command;
	
	return command;
}

void CommandProcessor::saveCommand(string toSave)
{
	Command* command = new Command(toSave, "");
	commands.push_back(command);
}

bool CommandProcessor::validate(string command)
{
	return true;
}

// FileCommandProcessorAdapter Class
FileCommandProcessorAdapter::FileCommandProcessorAdapter(CommandProcessor* cp)
{

}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* flr)
{

}

void FileCommandProcessorAdapter::getCommand(ifstream* file)
{
	string enteredCommand = readCommand(file);
	if (validate(enteredCommand))
	{
		saveCommand(enteredCommand);
	}
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

	getline(*file, next);

	return next;
}