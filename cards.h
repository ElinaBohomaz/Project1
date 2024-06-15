#pragma once

#include <vector>

#include "card.h"
#include "utilities.h"

class Cards
{
protected:
	std::vector<Card> cards;

public:
	size_t getCount();

	Card get(size_t index);
	void add(Card card);
	void add(std::vector<Card> cards);
	void clear();

	std::wstring toString();
	std::wstring toString(bool hidden);
};
