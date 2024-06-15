#pragma once

#include <stack>

#include "cards.h"
#include "permissions.h"
#include "utilities.h"
#include "card_deck.h"

class Player : public Cards
{
protected:
	int trump;

	void attack(std::vector<Card>* card_stack, int card_index);
	void discard(std::vector<Card>* card_stack);

public:
	Player();
	Player(int trump);

	bool canBeat(Card* card);
	bool canBeat(Card* attacker, Card* defender);
	bool canToss(std::vector<Card> card_stack);
	bool canToss(std::vector<Card> card_stack, Card* card);

	virtual bool action(std::vector<Card>* card_stack, int permissions);

	void takeCards(std::vector<Card>* cards_stack);
	void takeCards(CardDeck* card_deck);

	bool hasCards();
};
