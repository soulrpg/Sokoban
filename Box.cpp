#include "Box.h"

bool Box::check_collisions(Game_object* collider, int at_x, int at_y, Level& current_level)
{
	if (collider->get_symbol() == char(219) || collider->get_symbol() == char(207))
	{
		return true;
	}
	return false;
}

void Box::move_to(char dir, Level &current_level)
{
	Box::facing_dir = dir;
	int new_x;
	int new_y;
	if (Box::facing_dir == 'W')
	{
		new_x = Box::pos_x;
		new_y = Box::pos_y - 1;
	}
	if (Box::facing_dir == 'S')
	{
		new_x = Box::pos_x;
		new_y = Box::pos_y + 1;
	}
	if (Box::facing_dir == 'A')
	{
		new_x = Box::pos_x - 1;
		new_y = Box::pos_y;
	}
	if (Box::facing_dir == 'D')
	{
		new_x = Box::pos_x + 1;
		new_y = Box::pos_y;
	}
	current_level.set_field(pos_x, pos_y, 'O');
	current_level.set_field(new_x, new_y, 'X');
	current_level.clear_field(Box::pos_x, Box::pos_y);
	current_level.move_cursor(new_x, new_y);
	Box::draw();
	Box::pos_x = new_x;
	Box::pos_y = new_y;
	current_level.cursor_back();
	//std::cout << "Box pos_x: " << Box::pos_x << " pos_y: " << Box::pos_y << std::endl;
}