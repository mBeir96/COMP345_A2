#include "CommandProcessing.h"
#include "gameEngine.h"


//Command class
//default const
Command::Command()
{
	typed = "";
	effect = "";
}

//parameterize const
Command::Command(string typed, string effect)
{
	this->typed = typed;
	this->effect = effect;
}

//copy const
Command::Command(const Command& old)
{
	typed = old.typed;
	effect = old.effect;
}

//assignment op
Command& Command::operator=(const Command& t)
{
	if (this == &t)
	{
		return *this;
	}
	typed = t.typed;
	effect = t.effect;

	return *this;
}

//in stream op
std::istream& operator>>(std::istream& in, Command& t)
{
	return in;
}

//out stream op
std::ostream& operator<<(std::ostream& out, const Command& t)
{
	out << t.typed << ": " << t.effect;
	return out;
}

//Save Effect Method
void Command::saveEffect(CommandProcessor* cp, string effect)
{
	cp->commands.back()->effect = effect;
	LogObserver* lo = new LogObserver(this);
	Notify(this, effect);
}



void Command::stringToLog(string l)
{
	ofstream outFile;
	outFile.open("gamelog.txt", std::ios_base::app);
	outFile << "\nEffect: " + l;
	outFile.close();
}

//CommandProcessor class
//default const
CommandProcessor::CommandProcessor()
{
	commands;
}


//copy const
CommandProcessor::CommandProcessor(const CommandProcessor& old)
{
	commands = old.commands;
}

//assignment op
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& t)
{
	if (this == &t)
	{
		return *this;
	}
	commands = t.commands;

	return *this;
}

//in stream op
std::istream& operator>>(std::istream& in, CommandProcessor& t)
{
	return in;
}

//out stream op
std::ostream& operator<<(std::ostream& out, const CommandProcessor& t)
{
	string c = "";
	for (int i = 0; i < t.commands.size(); i++)
	{
		c = c + t.commands.at(i)->typed + ": " + c + t.commands.at(i)->effect + "\n";
	}
	out << c;
	return out;
}

//getCommand
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

//readCommand
string CommandProcessor::readCommand()
{
	string command;
	cin >> command;
	return command;
}

//saveCommand
void CommandProcessor::saveCommand(string toSave)
{
	Command* command = new Command(toSave, "");
	commands.push_back(command);
	LogObserver* lo = new LogObserver(this);
	Notify(this, toSave);
}

//validate
bool CommandProcessor::validate(int state, string command)
{
	// checking if each command is in the right state
	if (command == "loadmap" && (state == 0 || state == 1))
		return true;
	if (command == "tournament" && state == 0)
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

//stringToLog
void CommandProcessor::stringToLog(string l)
{
	ofstream outFile;
	outFile.open("gamelog.txt", std::ios_base::app);
	outFile << "\nCommand: " + l;
	outFile.close();
}


// FileCommandProcessorAdapter Class
//default const
FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
	commands;
	cp = NULL;
	flr = NULL;
}

//parameterized const when cp
FileCommandProcessorAdapter::FileCommandProcessorAdapter(CommandProcessor* cp)
{
	commands;
	this->cp = cp;
	flr = NULL;
}

//parameterized const when flr
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* flr)
{
	commands;
	cp = NULL;
	this->flr = flr;
}

//copy const
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& old)
{
	commands;
	cp = old.cp;
	flr = old.flr;
}

//assignment op
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& t)
{
	if (this == &t)
	{
		return *this;
	}
	commands;
	cp = t.cp;
	flr = t.flr;

	return *this;
}

//in stream op
std::istream& operator>>(std::istream& in, FileCommandProcessorAdapter& t)
{
	return in;
}

//out stream op
std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter& t)
{
	string c = "";
	for (int i = 0; i < t.commands.size(); i++)
	{
		c = c + t.commands.at(i)->typed + ": " + c + t.commands.at(i)->effect + "\n";
	}
	out << c;
	return out;
}

//getCommand when cp
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

//getCommand when flr
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

//readCommand when cp
string FileCommandProcessorAdapter::readCommand()
{
	string command;

	cin >> command;

	return command;
}

//readCommand when flr
string FileCommandProcessorAdapter::readCommand(ifstream* file)
{
	string command = flr->readLineFromFile(file);
	return command;
}



// FileLineReader Class
//default const (empty because there are no variables to initialize)
FileLineReader::FileLineReader()
{

}

//copy const
FileLineReader::FileLineReader(const FileLineReader& old)
{

}

//assignment op
FileLineReader& FileLineReader::operator=(const FileLineReader& t)
{
	if (this == &t)
	{
		return *this;
	}


	return *this;
}

//in stream op
std::istream& operator>>(std::istream& in, FileLineReader& t)
{
	return in;
}

//out stream op
std::ostream& operator<<(std::ostream& out, const FileLineReader& t)
{
	out;
	return out;
}

//readLineFromFile
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