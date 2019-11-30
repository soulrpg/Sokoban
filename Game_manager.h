#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "Level.h"

////////////////////////
// Klasa zajmuje si� tworzeniem g��wnego menu w kt�rym wyboru mo�e dokona� u�ytkownik oraz zapewnia implementacje funkcji do 
// wczytywania stanu gry/poziom�w z pliku i zapisywania stanu gry do pliku.
////////////////////////

class Game_manager
{
private:
	int number_of_levels;
	int level_load_id;
	char choice;
	Level current_level;
public:
	Game_manager(int max_levels);
	void main_menu();
	Level load_level();
	Level load_state();
	void save_state();
};

