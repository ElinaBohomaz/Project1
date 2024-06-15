#pragma once

#include <iostream>
#include <string>

#include "ranks.h"
#include "suits.h"
#include "utilities.h"

struct Card
{
	int rank;
	int suit;

	bool isTrump(int suit);
	std::wstring toString();
};
