#pragma once
#include <iostream>

////////////////////////
// Ta klasa s�u�y do tworzenia dw�ch typ�w obiekt�w - pustych pul (wolnych) oraz �cian kt�re blokuj� ruch skrzy� i gracza.
// S� to obiekty, kt�re nie mog� si� porusza� po planszy, kiedy raz zostan� ustawione. symbol okre�la ich grafik� (znak), kt�ry
// b�dzie wy�wietlany.
////////////////////////

class Game_object
{
protected:
	int pos_x;
	int pos_y;
	char symbol;
public:
	Game_object(int x, int y, char s);
	char get_symbol();
	int get_pos_x();
	int get_pos_y();
	virtual void draw();
};

