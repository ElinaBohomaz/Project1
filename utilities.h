#pragma once

#include <iostream>
#include <string>
#include <sstream>

enum Colors
{
    reset = 0,
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    magenta = 35,
    cyan = 36,
    white = 37,
    gray = 90,
    bright_black = 90,
    bright_red = 91,
    bright_green = 92,
    bright_yellow = 93,
    bright_blue = 94,
    bright_magenta = 95,
    bright_cyan = 96,
    bright_white = 97,
    bright_gray = 37
};

void clear();
void pause();
std::wstring getValue();
std::wstring getValue(const wchar_t* description);
bool wstringToInt(std::wstring string, int &buffer);
std::wstring textColor(const std::wstring& text, int color);
