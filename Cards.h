#pragma once

#include "Orders.h";
#include <list>;
#include <vector>;
#include <string>;

enum CardType { Bomb, Reinforcement, Airlift, Diplomacy, Blockade };

//all class need to have an assignment operator, and stream insertion operator.

class Card
{
	public:
		//Card Constructors
		Card(CardType givenType);
		Card(const Card &card);
		
		//card destructor
		~Card();

		Card& operator = (const Card& c);
		friend std::istream& operator>>(std::istream& in, Card& c);
    	friend std::ostream& operator<<(std::ostream &out, const Card &c);
		
		//this is a dummy function meant to print card type
		//this is not meant to be used during the actual gamevoid PrintCardType();
		void PrintCardType();

		CardType GetCardType();
		Orders* Play();
	private:
		CardType* cardType;
};

class Deck
{
	public:
		Deck();
		Deck(const Deck &deck);
		Deck& operator = (const Deck& d);
		friend std::istream& operator>>(std::istream& in, Deck& d);
    	friend std::ostream& operator<<(std::ostream &out, const Deck &d);
		~Deck();
		void ShowCards();
		void AddCard(Card* card);
		Card* Draw();
	private:
		std::vector<Card *>* cards;
};

class Hand
{
	public:
		Hand();
		Hand(const Hand &hand);
		Hand& operator = (const Hand& h);
		friend std::istream& operator>>(std::istream& in, Hand& h);
    	friend std::ostream& operator<<(std::ostream &out, const Hand &h);
		~Hand();
		void AddCard(Card* card);
		void ShowCards();
		Card * Draw(int position);
	private:
		std::vector<Card*>* cards;
};

void PlayCard(Deck*, Hand*, int);