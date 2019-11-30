#include "Game_object.h"

Game_object::Game_object(int x, int y, char s)
{
	Game_object::pos_x = x;
	Game_object::pos_y = y;
	Game_object::symbol = s;
}

char Game_object::get_symbol()
{
	return Game_object::symbol;
}

int Game_object::get_pos_x()
{
	return Game_object::pos_x;
}

int Game_object::get_pos_y()
{
	return Game_object::pos_y;
}

void Game_object::draw()
{
	std::cout << symbol;
}

