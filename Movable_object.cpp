#include "Movable_object.h"
#include "Level.h"
#include "Box.h"

Movable_object::Movable_object(int x, int y, char s, char f):Game_object(x, y, s)
{
	Movable_object::facing_dir = f;
}


// Trzeba to zrobiæ rekurencyjnie dla kolejnego obiektu (skrzyni, jeœli to ona bêdzie na drodze)
void Movable_object::move_to(char f, Level &current_level)
{
	//std::cout << "Movin: " << f  << std::endl;
	Movable_object::facing_dir = f;
	int new_x;
	int new_y;
	if (Movable_object::facing_dir == 'W')
	{
		new_x = Movable_object::pos_x;
		new_y = Movable_object::pos_y-1;
	}
	if (Movable_object::facing_dir == 'S')
	{
		new_x = Movable_object::pos_x;
		new_y = Movable_object::pos_y+1;
	}
	if (Movable_object::facing_dir == 'A')
	{
		new_x = Movable_object::pos_x-1;
		new_y = Movable_object::pos_y;
	}
	if (Movable_object::facing_dir == 'D')
	{
		new_x = Movable_object::pos_x+1;
		new_y = Movable_object::pos_y;
	}
	bool has_collided;
	has_collided = (this->check_collisions(current_level.get_field(new_x, new_y), new_x, new_y, Movable_object::facing_dir, current_level) ? true : false);
	if (has_collided == false)
	{
		//std::cout << "Brak kolizji" << std::endl;
		current_level.set_field(pos_x, pos_y, 'O');
		current_level.set_field(new_x, new_y, '@');
		current_level.clear_field(Movable_object::pos_x, Movable_object::pos_y);
		current_level.move_cursor(new_x, new_y);
		Movable_object::draw();
		Movable_object::pos_x = new_x;
		Movable_object::pos_y = new_y;
	}
}

bool Movable_object::check_collisions(Game_object* collider, int at_x, int at_y, char dir, Level &current_level)
{
	// Przypadek w którym gracz koliduje ze œcian¹
	if (collider->get_symbol() == char(219))
	{
		return true;
	}
	// Przypadek w którym gracz koliduje ze skrzyni¹ - wywo³ujemy na niej rekurencyjnie próbê przemieszczenia
	else if (collider->get_symbol() == char(207))
	{
		if (dir == 'W')
		{
			if (((Box*)collider)->check_collisions(current_level.get_field(at_x, at_y - 1), at_x, at_y - 1, current_level))
			{
				return true;
			}
			else
			{
			}
		}
		if (dir == 'S')
		{
			if (((Box*)collider)->check_collisions(current_level.get_field(at_x, at_y + 1), at_x, at_y + 1, current_level))
			{
				return true;
			}
		}
		if (dir == 'A')
		{
			if (((Box*)collider)->check_collisions(current_level.get_field(at_x-1, at_y), at_x-1, at_y, current_level))
			{
				return true;
			}
		}
		if (dir == 'D')
		{
			if (((Box*)collider)->check_collisions(current_level.get_field(at_x + 1, at_y), at_x + 1, at_y, current_level))
			{
				return true;
			}
		}
		//std::cout << "DIr: " << dir << std::endl;
		((Box*)collider)->move_to(dir, current_level);
	}
	return false;
}
