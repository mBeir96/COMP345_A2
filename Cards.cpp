#include "Cards.h";
#include <list>;
#include <random>;
#include <iostream>;
#include <string>;

class Deck;
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
		orders = new BombOrders();
		break;
	case Airlift:
		orders = new AirliftOrders();
		break;
	case Blockade:
		orders = new BlockadeOrders();
		break;
	case Reinforcement:
		orders = new DeployOrders();
		break;
	case Diplomacy:
		orders = new NegotiateOrders();
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
	fillDeck(this);
	random_shuffle(cards->begin(), cards->end());
}

Deck::Deck(const Deck& deck)
{
	this->cards = deck.cards;
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

void Deck::fillDeck(Deck* d)
{
	//adding bomb Cards
	Card* bomb[10];
	for (int i = 0; i < 10; i++)
	{
		bomb[i] = new Card(Bomb);
		d->AddCard(bomb[i]);
	}
	//adding reinforcement Cards
	Card* reinforcement[10];
	for (int i = 0; i < 10; i++)
	{
		reinforcement[i] = new Card(Reinforcement);
		d->AddCard(reinforcement[i]);
	}
	//adding Airlift Cards
	Card* airlift[10];
	for (int i = 0; i < 10; i++)
	{
		airlift[i] = new Card(Airlift);
		d->AddCard(airlift[i]);
	}
	//adding Diplomacy Cards
	Card* diplomacy[10];
	for (int i = 0; i < 10; i++)
	{
		diplomacy[i] = new Card(Diplomacy);
		d->AddCard(diplomacy[i]);
	}
	//adding Blockade Cards
	Card* blockade[10];
	for (int i = 0; i < 10; i++)
	{
		blockade[i] = new Card(Blockade);
		d->AddCard(blockade[i]);
	}
}

void Deck::AddCard(Card* card)
{
	cards->push_back( card);
}


Card* Deck::Draw()
{
	if (this->cards->empty())
	{
		this->fillDeck(this);
	}

	int rand = std::rand() % cards->size();
	Card* temp = cards->at(rand);
	cards->erase(cards->begin() + rand);
	return temp;
}
#pragma endregion

#pragma region Hand

Hand::Hand()
{
	cards = new vector<Card*>;
}

Hand::Hand(const Hand& hand)
{
	this->cards = hand.cards;
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
	if (this->cards != nullptr)
	{
		while (!cards->empty()) {
			delete(cards->front());
			cards->erase(cards->begin());
		}
	}
	

	delete cards;
	cards = NULL;

}

void Hand::AddCard(Card* card)
{
	cards->push_back(card);

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
