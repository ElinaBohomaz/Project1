#include "utilities.h"

void clear()
{
	system("cls");
}

void pause()
{
	system("pause");
}

std::wstring getValue()
{
	std::wstring buffer;
	std::wcin >> buffer;
	std::wcin.clear();
	return buffer;
}


std::wstring getValue(const wchar_t* description)
{
	std::wstring buffer;

	std::wcout << description << L": ";
	std::wcin >> buffer;

	std::wcin.clear();

	return buffer;
}

bool wstringToInt(std::wstring string, int &buffer)
{
	try
	{
		buffer = (std::stoi(string));
	}
	catch (...)
	{
		return false;
	}

	return true;
}

std::wstring textColor(const std::wstring& text, int color)
{
	std::wstringstream stream;

	stream << L"\033[" << color << L"m" << text << L"\033[0m";

	return stream.str();
}
