#include "Cards.h";
#include "Orders.h";
#include <list>;
#include <random>;
#include <iostream>;
#include <string>;


//Get text version of enums
const char* CardNames[] = {
	"Bomb",
	"Reinforcement",
	"Airlift",
	"Diplomacy",
	"Blockade"
};

#pragma region Card

Card::Card(CardType givenType)
{
	//Set card type
	cardType = new CardType{ givenType };
}

Card::Card(const Card& card)
{
	//Set card type
	cardType = card.cardType;
}

Card& Card::operator=(const Card& c)
{
    if (this == &c)
	{
    	return *this;
    }
    cardType = new CardType(*(c.cardType));

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Card& c)
{
    out << c.cardType << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Card& c)
{
    return in;
}

Card::~Card()
{
	//delete card type
	delete(cardType);
}


void Card::PrintCardType()
{
	std::cout <<  CardNames[*cardType];
	std::cout << "\n";
}

//gets card type
CardType Card::GetCardType() {
	return *cardType;
}


Orders* Card::Play()
{
	Orders* orders;
	switch (*cardType)
	{
	case Bomb:
		//switch when bomb orders is no longer abstract
		orders = nullptr;
		//orders = new BombOrders();
		break;
	case Airlift:
		orders = new AirliftOrders();
		break;
	case Blockade:
		orders = new BlockadeOrders();
		break;
	default:
		orders = nullptr;
	}

	return orders;
}

#pragma endregion

#pragma region Deck

Deck::Deck()
{
	cards = new std::vector<Card*>;
}

Deck::Deck(const Deck& deck)
{
}

Deck& Deck::operator=(const Deck& d)
{
    if (this == &d)
	{
    	return *this;
    }
    this->cards = d.cards;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Deck& d)
{
    out << d.cards << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Deck& d)
{
    return in;
}

Deck::~Deck()
{
	while (!cards->empty()) {
		delete(cards->front());
		cards->erase(cards->begin());
	}

	delete(cards);
}

void Deck::ShowCards()
{
	for (int i = 0; i < cards->size(); i++) {
		cards->at(i)->PrintCardType();
	}
}

void Deck::AddCard(Card* card)
{
	cards->push_back( card);
}


Card* Deck::Draw()
{
	int rand = std::rand() % cards->size();
	Card* temp = cards->at(rand);
	cards->erase(cards->begin() + rand);
	return temp;
}
#pragma endregion

#pragma region Hand

Hand::Hand()
{
	cards = new std::vector<Card*>;
}

Hand::Hand(const Hand& hand)
{
}

Hand& Hand::operator=(const Hand& h)
{
    if (this == &h)
	{
    	return *this;
    }
    this->cards = h.cards;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Hand& h)
{
    out << h.cards << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Hand& h)
{
    return in;
}

Hand::~Hand()
{
	while (!cards->empty()) {
		delete(cards->front());
		cards->erase(cards->begin());
	}

	delete(cards);
}

void Hand::AddCard(Card* card)
{
	cards->push_back( card);

}

void Hand::ShowCards()
{
	for (int i = 0; i < cards->size(); i++) {
		cards->at(i)->PrintCardType();
	}
}

Card* Hand::Draw(int position)
{
	Card *temp = cards->at(position);
	cards->erase(cards->begin() + position);
	return temp;
}

#pragma endregion

void PlayCard(Deck* deck, Hand* hand, int position)
{
	Card* card = hand->Draw(position);
	deck->AddCard(card);
}
