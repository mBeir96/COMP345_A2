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
		~Hand();
		void AddCard(Card* card);
		void ShowCards();
		Card * Draw(int position);
	private:
		std::vector<Card*>* cards;
};

void PlayCard(Deck*, Hand*, int);