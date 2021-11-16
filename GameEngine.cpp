#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

//constructors and stuff
GameEngine::GameEngine()
{
    this->StartUp = false;
    this->Play = false;

    theMap = new Map();
    loader = new MapLoader;
    loadedMap = NULL;

    cp = new CommandProcessor();
    flr = new FileLineReader();
    inFile;

    players;

    deck = new Deck();
}

//param const
GameEngine::GameEngine(bool StartUp, bool Play)
{
    this->StartUp = StartUp;
    this->Play = Play;
}

//copy const
GameEngine::GameEngine(const GameEngine& g)
{
    StartUp = new bool(g.StartUp);
    Play = new bool(g.Play);
}

//destructor
GameEngine::~GameEngine()
{
    
    delete loader;
    delete loadedMap;
    delete cp;
    delete flr;
    delete deck;
    delete theMap;
    theMap = NULL;
    loader = NULL;
    loadedMap = NULL;
    cp = NULL;
    flr = NULL;
    deck = NULL;
    std::cout << "Game Engine successfully destroyed" << std::endl;
}

//assignment op
GameEngine& GameEngine::operator=(const GameEngine& g)
{
    if (this == &g)
    {
        return *this;
    }
    StartUp = new bool(g.StartUp);
    Play = new bool(g.Play);

    return *this;
}

//out tsream
std::ostream& operator<<(std::ostream& out, const GameEngine& g)
{
    out << g.StartUp << " " << g.Play << std::endl;
    return out;
}

//in stream
std::istream& operator>>(std::istream& in, GameEngine& g)
{
    return in;
}

//counts how many commands have been issued
int GameEngine::CommandCount = 0;

//states and gameplay
int state;
int getState()
{
    return state;
}

//Start state
void GameEngine::Start() {
    cout << "Welcome to the game " << endl;
    cout << "Please enter a command using the console (by typing -console) or a file (-file filename)" << endl;

    string a;
    string command;
    cin >> a;

    //if they want to input a command from console
    if (a == "-console") 
    {
        processor.cp = cp;
        //loadmap when they command loadmap
        if (processor.getCommand(state) == "loadmap")
        {
            CommandCount++;
            string file_name;
            cin >> file_name;

            ifstream inFile(file_name.c_str());

            if (!inFile)
            {
            	cerr << "unable to open input file: " << file_name << " ending program!\n";
            }

            loadedMap = loader->readMap(file_name);
            if (loadedMap != NULL)
                {
                theMap->theMap = loader->readMap(file_name);
                }
            processor.commands.at(CommandCount - 1)->saveEffect(&processor, file_name);
            state = 1;
        }
        
    }
    //if they want to use a file
    else if (a == "-file")
    {
        cin >> a;
        processor.flr = flr;
        inFile.open(a.c_str());

        if (!inFile)
        {
            cerr << "unable to open input file: " << a << "\n";
        }

        if (processor.getCommand(state, &inFile) != "")
        {
            CommandCount++;
            string file = processor.readCommand(&inFile);
            loadedMap = loader->readMap(file);
            if (loadedMap != NULL)
            {
                theMap->theMap = loader->readMap(file);
            }
            processor.commands.at(CommandCount - 1)->saveEffect(&processor, file);
            state = 1;
        }
        
    }
    
}

//Map loaded state
void GameEngine::MapLoaded() {

    cout << "Map is Loaded. You can Load a new map (loadmap) or validate the map you have (validatemap)\nStart with -console or -file" << endl;
    string isValid;
    cin >> isValid;

    //if they want to use console
    if (isValid == "-console")
    {
        processor.cp = cp;
        processor.flr = NULL;
        isValid = processor.getCommand(state);
        //load map brings them back to start stage
        if (isValid == "loadmap") 
        {
            CommandCount++;
            processor.commands.at(CommandCount - 1)->saveEffect(&processor, "Returned to Start");
            state = 1;
            Start();
        }
        //validates map
        else if (isValid == "validatemap") 
        {
            CommandCount++;
            if (theMap->validate())
            {
                processor.commands.at(CommandCount - 1)->saveEffect(&processor, "Validated Map");
                state = 2;
            }  
            else
            {
                processor.commands.at(CommandCount - 1)->saveEffect(&processor, "Invalid Map: Returned to Start");
                cout << "Invalid Map. Please load a new one";
                state = 1;
                Start();
            }
            
        }
    }

    //if they want to use file
    else if (isValid == "-file")
    {
        
        processor.cp = NULL;
        processor.flr = flr;
        //checks if user want to use the same file as before
        if (!inFile.is_open())
        {
            cin >> isValid;
            inFile.open(isValid);
        }
        else
        {
            cout << "Use the same file as before? (y/n)";
            cin >> isValid;
            if (isValid == "n")
            {
                inFile.close();
                cout << "\nEnter new file name: ";
                cin >> isValid;
                inFile.open(isValid);
            }
        }
        isValid = processor.getCommand(state, &inFile);
        //loadmap takes them back to start
        if (isValid == "loadmap")
        {
            CommandCount++;
            processor.commands.at(CommandCount - 1)->saveEffect(&processor, "Returned to Start");
            state = 1;
            Start();
        }
        //validate map
        else if (isValid == "validatemap")
        {
            CommandCount++;
            if (theMap->validate())
            {
                processor.commands.at(CommandCount - 1)->saveEffect(&processor, "Validated Map");
                state = 2;
            }
            else
            {
                processor.commands.at(CommandCount - 1)->saveEffect(&processor, "Invalid Map: Returned to Start");
                cout << "Invalid Map. Please load a new one";
                state = 1;
                Start();
            }

        }
    }

}
//vmapvalidated state
void GameEngine::MapValidated() {
    cout << "\n\nMap Has Been Validated. Now you can start adding players by writting \"addplayer player\" \n start with -console or -file" << endl;

    string a;
    cin >> a;
    //if they want to use console
    if (a == "-console")
    {
        processor.cp = cp;
        processor.flr = NULL;
        a = processor.getCommand(state);
        if (a == "addplayer")
        {
            //gets player name
            a = processor.readCommand();
            Player* one = new Player(a);
            //put player in players vector because it's impossible for them to have more than 6 players at this state
            players.push_back(one);
            CommandCount++;
            processor.commands.at(CommandCount - 1)->saveEffect(&processor, "added player " + a);
            cout << "\nPlayer " << players.size() << " added.";
            state = 3;
        }
    }
    //if they want to use file
    else if (a == "-file")
    {

        processor.cp = NULL;
        processor.flr = flr;
        //checks if file is already open and if they want to use the same file
        if (!inFile.is_open())
        {
            cin >> a;
            inFile.open(a);
        }
        else
        {
            cout << "Use the same file as before? (y/n)";
            cin >> a;
            if (a == "n")
            {
                inFile.close();
                cout << "\nEnter new file name: ";
                cin >> a;
                inFile.open(a);
            }
        }
        a = processor.getCommand(state, &inFile);
        if (a == "addplayer")
        {
            //gets player name
            a = processor.readCommand(&inFile);
            Player* one = new Player(a);
            //put player in players vector because it's impossible for them to have more than 6 players at this state
            players.push_back(one);
            CommandCount++;
            processor.commands.at(CommandCount - 1)->saveEffect(&processor, "added player " + a);
            cout << "\nPlayer " << players.size() << " added.";
            state = 3;
        }
    }
}

//players added state
void GameEngine::PlayersAdded() {
    cout << "Enter \"addplayer\" to add player (minimum 2, maximum 6), or \"gamestart\" to go to the next state" << endl;
    string a;
    cin >> a;
    //if they want to use console
    if (a == "-console")
    {
        processor.cp = cp;
        processor.flr = NULL;
        a = processor.getCommand(state);
        if (a == "addplayer") 
        {
            //checks if we have less than 6 players (since thats the max)
            if (players.size() < 6)
            {
                a = processor.readCommand();
                Player* one = new Player(a);
                players.push_back(one);
                CommandCount++;
                processor.commands.at(CommandCount - 1)->saveEffect(&processor, "added player " + a);
                cout << "\nPlayer " << players.size() << " added.";
                state = 3;
            }
            else
            {
                cout << "Maximum amount of players achieved, moving to state \"AssignReinforcement\"";
                state = 4;
            }
                
            
        }
        //goes to game start if we have 2 or more players
        else if (a == "gamestart") 
        {
            if (players.size() >= 2)
            {
                state = 4;
            }
            else
            {
                cout << "Only one player. Please add at least another before going to next state. ";
                state = 3;
            }
            
        }
    }
    //if they want to use a file
    else if (a == "-file")
    {

        processor.cp = NULL;
        processor.flr = flr;
        //checks if file is open and if they want to use the same one
        if (!inFile.is_open())
        {
            cin >> a;
            inFile.open(a);
        }
        else
        {
            cout << "Use the same file as before? (y/n)";
            cin >> a;
            if (a == "n")
            {
                inFile.close();
                cout << "\nEnter new file name: ";
                cin >> a;
                inFile.open(a);
            }
        }
        a = processor.getCommand(state, &inFile);
        //adddplayer command if there is less than 6 players
        if (a == "addplayer")
        {
            if (players.size() < 6)
            {
                a = processor.readCommand(&inFile);
                Player* one = new Player(a);
                players.push_back(one);
                CommandCount++;
                //saveeffect
                processor.commands.at(CommandCount - 1)->saveEffect(&processor, "added player " + a);
                cout << "\nPlayer " << players.size() << " added.";
                state = 3;
            }
            else
            {
                cout << "Maximum amount of players achieved, movinf to state \"AssignReinforcement\"";
                state = 4;
            }


        }
        //goes to gamestart if there 2 or more players
        else if (a == "gamestart")
        {
            if (players.size() >= 2)
            {
                state = 4;
            }
            else
            {
                cout << "Only one player. Please add at least another before going to next state. ";
                state = 3;
            }

        }
    }
}

//AasignReinforcement state
void GameEngine::AssignReinforcement() {

    cout << "\nEnter \"continue\" to assign reinforcements and begin to play" << endl;
    string a;
    cin >> a;
    if (a == "continue") 
    {
        //dividing the territories to the players 
        //making the player own the territory
        for (int i = 0; i < theMap->theMap->size(); i++)
        {
            players.at(i % players.size())->setTerritory(&(theMap->theMap->at(i)));
        }
        //initializing play order
        random_shuffle(players.begin(), players.end());
        //giving every player 50 initial armies to their reinforcement pool
        for (int i = 0; i < players.size(); i++)
        {
            players.at(i)->setReinforcementPool(50);
        }
        //giving every player 2 draws
        for (int i = 0; i < players.size(); i++)
        {
            players.at(i)->setHand(deck->Draw());
            players.at(i)->setHand(deck->Draw());
        }
        for (int i = 0; i < players.size(); i++)
        {
            cout << players.at(i)->getName() << ": ";
            players.at(i)->handCard->ShowCards();
        }
        state = 5;
        //calling play function
        play();
    }

}
void GameEngine::IssueOrders() {
    cout << "\nNow starting The Game! Enter \"issueorder\" or \"endgame\" " << endl;
    string a;
    cin >> a;
    if (a == "issueorder") {
        cout << "Issue Order" << endl;
        state = 5;
    }
    else if (a == "endgame") {
        state = 6;
    }

}
void GameEngine::exec() {
    for each (Player * player in players)
    {
        for (int i = 0; i < player->orderList.size(); i++)
        {
            //execute and remove if its a deploy order
            if (player->orderList.at(i)->getName() == "Deploy Orders")
            {
                //validate, excute and delete order
                player->orderList.at(i)->validate(true);
                player->orderList.at(i)->execute();
                player->orderList.erase(player->orderList.begin() + i);
                i--;
            }
        }
    }

    //there should be no more deploy orders

    for each (Player * player in players)
    {
        while (!player->orderList.empty())
        {
            //validate, excute and delete order
            player->orderList.at(0)->validate(true);
            player->orderList.at(0)->execute();
            player->orderList.erase(player->orderList.begin());
        }
    }

    //order list should be empty
}

void GameEngine::ExecuteOrders() {
    
    
    cout << "Enter \"win\" to win,  Enter \"executeOrder\" to repeat executeOrder Enter \"new\"to go back to issue new order" << endl;
    string a;
    cin >> a;
    if (a == "win") {

        state = 7;
    }
    else if (a == "executeOrder") {
        exec();
        state = 6;
    }
    else if (a == "new") {
        state = 5;
        issueOrder();
    }
    

    
}

//Win state
void GameEngine::Win() {

    cout << "Enter \"replay\" to play again,  Enter \"quit\" to exit the program\n start with \"-console\" or \"-file\"" << endl;
    string a;
    cin >> a;

    //if they want to use console
    if (a == "-console")
    {
        processor.cp = cp;
        processor.flr = NULL;
        a = processor.getCommand(state);
        //replay brings them back to start
        if (a == "replay")
        {
            CommandCount++;
            processor.commands.at(CommandCount - 1)->saveEffect(&processor, "Back to Start");
            state = 0;
            Start();
        }
        //quit prints the commands and effects used during the game and exits the game
        else if (a == "quit")
        {
            cout << "Exiting Game! Hope you had fun!" << endl;
            CommandCount++;
            processor.commands.at(CommandCount - 1)->saveEffect(&processor, "Ending game");
            for (int i = 0; i < processor.commands.size(); i++)
            {
                cout << "\n" << i << " " << processor.commands.at(i)->typed << " " << processor.commands.at(i)->effect;
            }
            cin >> a;
            if (a == "yes")
            {
                state = 8;
            }
            
        }
    
    }
}

//startupPhase method loops every state until state change
void GameEngine::StartupPhase() {
    while (state == 0) 
    {
        Start();
    }
    while (state == 1) {
        MapLoaded();
    }
    while (state == 2) {
        MapValidated();
    }
    while (state == 3) {
        PlayersAdded();
    }
    while (state == 4) {
        AssignReinforcement();
    }
}

//play method loops every state until state change
void GameEngine::play()
{
        while (state == 5) {
            IssueOrders();
        }
        while (state == 6) {
            ExecuteOrders();
        }
        while (state == 7) {
            Win();
        }
}





bool GameEngine::getStartUp() {
    return StartUp;
}
bool GameEngine::getPlay() {
    return Play;
}
void GameEngine::setStartUp(bool StartUp) {
    this->StartUp = StartUp;
}
void GameEngine::setPlay(bool Play) {
    this->Play = Play;
}

void GameEngine::currentState() {

}

void GameEngine::changeState() {

}


void GameEngine::loadMap() {
    //add code here later 
}
void GameEngine::validateMap() {
    //add code here later 
}
void GameEngine::addPlayer() {
    //add code here later 
}
void GameEngine::issueOrder() {
    //add code here later 
}
void GameEngine::executeOrder() {
    //add code here later 
}
void GameEngine::endExecuteOrder() {
    //add code here later 
}
void GameEngine::win() {
    //add code here later 
}
