#pragma once
#include <iostream>

////////////////////////
// Ta klasa s³u¿y do tworzenia dwóch typów obiektów - pustych pul (wolnych) oraz œcian które blokuj¹ ruch skrzyñ i gracza.
// S¹ to obiekty, które nie mog¹ siê poruszaæ po planszy, kiedy raz zostan¹ ustawione. symbol okreœla ich grafikê (znak), który
// bêdzie wyœwietlany.
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

