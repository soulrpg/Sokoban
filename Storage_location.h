#pragma once
#include <Windows.h>
//#include "Level.h"
#include "Game_object.h"

////////////////////////
// Storage_location to zwyk�y obiekt, kt�ry nie mo�e si� porusza� z t� r�nic�, �e ma pole is_filled, kt�re okre�la czy znajduje si� na nim
// jaka� skrzynka. Opr�cz tego nadpisuje funkcj� draw() z tego wzgl�du, �e w przypadku Storage_location nie b�dzie wy�wietlany zwyk�y znak w
// konsoli, lecz t�o miejsca na kt�rym ma si� znajdowa� pusty znak b�dzie pokolorowane na inny kolor.
////////////////////////

class Storage_location : public Game_object
{
private:
	bool is_filled;
public:
	Storage_location(int x, int y, char s);
	//bool check_if_filled(Level &current_level);
	void set_filled();
	void unset_filled();
	void draw(bool player_on);
};

