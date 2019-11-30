#pragma once
#include "Game_object.h"
//#include "Level.h"

////////////////////////
// Ta klasa s³u¿y do tworzenia dwóch typów obiektów - gracza i skrzyñ.
// S¹ to obiekty które mog¹ siê poruszaæ. Oprócz pozosta³ych pul dziedziczonych z Game_object (x, y, symbol) maj¹ pole facing_dir
// które okreœla w któr¹ stronê skierowany jest obiekt (W - góra, S - dó³, A - lewo, D - prawo).
// W przypadku gracza wiadomo o co chodzi, w przypadku skrzyñ bêdzie to przydatne podczas sprawdzania czy jeœli gracz popchnie dan¹ skrzyniê
// to czy kieruje siê ona na jakieœ pole zawieraj¹ce œcianê (blokadê).
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

