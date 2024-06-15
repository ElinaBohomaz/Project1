#pragma once

#include <iostream>

enum Ranks
{
	six = 6,
	seven,
	eight,
	nine,
	ten,
	jack,    // Валет
	queen,  // Дама
	king,  // Король
	ace   // Туз
};

extern std::wstring str_ranks[4];
