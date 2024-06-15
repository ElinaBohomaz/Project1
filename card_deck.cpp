#include "card_deck.h"

#include <random>

void CardDeck::init()
{
	for (int rank = Ranks::six; rank <= Ranks::ace; rank++)
	{
		for (int suite = Suits::diamonds; suite <= Suits::clubs; suite++)
		{
			add(Card{ rank, suite });
		}
	}

	this->trump = this->cards[0];
}

void CardDeck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());

	for (int i = 0; i < 7; i++)
	{
		std::shuffle(cards.begin(), cards.end(), g);
	}

	this->trump = this->cards[0];
}

Card CardDeck::getTrump()
{
	return this->trump;
}

Card CardDeck::pop()
{
	if (cards.empty())
	{
		return Card{ -1, -1 };
	}

	Card card = cards.back();
	cards.pop_back();

	return card;
}

bool CardDeck::isTrump(Card card)
{
	return trump.suit == card.suit;
}
