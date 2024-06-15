#pragma once

#include "player.h"

class Bot : public Player
{
protected:
	int getMinCardIndex(const std::vector<Card>& cards, int trump, bool onlyTrump);

public:
	Bot();
	Bot(int trump);

	bool action(std::vector<Card>* card_stack, int permissions);
};
