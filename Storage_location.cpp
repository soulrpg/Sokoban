#include "Storage_location.h"

Storage_location::Storage_location(int x, int y, char s):Game_object(x, y, s)
{
	Storage_location::is_filled = false;
}

void Storage_location::set_filled()
{
	Storage_location::is_filled = true;
}

void Storage_location::unset_filled()
{
	Storage_location::is_filled = false;
}

void Storage_location::draw(bool player_on)
{
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout, 23);
	if (Storage_location::is_filled)
	{
		std::cout << char(207);
	}
	else if (player_on)
	{
		std::cout << "@";
	}
	else
	{
		std::cout << " ";
	}
	// Powrót do bazowych ustawieñ kolorów konsoli.
	SetConsoleTextAttribute(hout, 7);
}
