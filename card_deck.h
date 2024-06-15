#pragma once

#include "cards.h"

class CardDeck : public Cards
{
private:
	Card trump;  // Козирь 

public:
	void init();
	void shuffle();
	
	Card getTrump();
	Card pop();

	bool isTrump(Card card);
};
