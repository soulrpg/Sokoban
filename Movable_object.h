#pragma once
#include "Game_object.h"
//#include "Level.h"

////////////////////////
// Ta klasa s�u�y do tworzenia dw�ch typ�w obiekt�w - gracza i skrzy�.
// S� to obiekty kt�re mog� si� porusza�. Opr�cz pozosta�ych pul dziedziczonych z Game_object (x, y, symbol) maj� pole facing_dir
// kt�re okre�la w kt�r� stron� skierowany jest obiekt (W - g�ra, S - d�, A - lewo, D - prawo).
// W przypadku gracza wiadomo o co chodzi, w przypadku skrzy� b�dzie to przydatne podczas sprawdzania czy je�li gracz popchnie dan� skrzyni�
// to czy kieruje si� ona na jakie� pole zawieraj�ce �cian� (blokad�).
////////////////////////

class Level;
class Box;

class Movable_object:public Game_object
{
protected:
	char facing_dir;
public:
	Movable_object(int x, int y, char s, char f);
	//void move_to(int new_x, int new_y, Level &current_level);
	void move_to(char f, Level &current_level);
	bool check_collisions(Game_object* collider, int at_x, int at_y, char dir, Level &current_level);
};

