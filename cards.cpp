#include "cards.h"

size_t Cards::getCount()
{
	return cards.size();
}

Card Cards::get(size_t index)
{
	return cards[index];
}

void Cards::add(Card card)
{
	this->cards.push_back(card);
}

void Cards::add(std::vector<Card> cards)
{
	this->cards.insert(this->cards.end(), cards.begin(), cards.end());
}

void Cards::clear()
{
	cards.clear();
}

std::wstring Cards::toString()
{
	std::wstring string;

	for (int i = 0; i < this->getCount(); i++)
	{
		string += std::to_wstring(i + 1) + L"." + cards[i].toString() + L"  ";
	}

	return string;
}

std::wstring Cards::toString(bool hidden)
{
	std::wstring string;

	for (int i = 0; i < this->getCount(); i++)
	{
		string += std::to_wstring(i + 1) + L".[##]  ";
	}

	return string;
}
