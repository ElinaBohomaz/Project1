#include "card.h"

bool Card::isTrump(int suit)
{
	return this->suit == suit;
}

std::wstring Card::toString()
{
	std::wstring card;

	card += L'[';

	card += this->rank > 10 ? str_ranks[this->rank - 11] : std::to_wstring(rank);
	card += str_suits[this->suit];

	card += L']';

	return textColor(card, suits_color[this->suit]);
}
