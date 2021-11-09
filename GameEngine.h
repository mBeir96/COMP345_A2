#pragma once

#include <iostream>
#include <string>
enum RiskState {
	START, MAPLOADED, MAPVALIDATED, PLAYERSADDED, ASSIGNMENTREIFORCEMENT, ISSUEORDERS, EXECUTEORDERS, WIN
};
class GameEngine {
	public:
		GameEngine();
		GameEngine(bool, bool);
		GameEngine(const GameEngine &g);
		GameEngine& operator=(const GameEngine& g);
        friend std::istream& operator>>(std::istream& in, GameEngine& g);
        friend std::ostream& operator<<(std::ostream &out, const GameEngine &g);
        ~GameEngine();
		void loadMap();
		void validateMap();
		void addPlayer();
		void issueOrder();
		void executeOrder();
		void endExecuteOrder();
		void win();
		bool getStartUp();
		bool getPlay();
		void setStartUp(bool);
		void setPlay(bool);
		
	private:
		bool StartUp;
		bool Play;
	
};