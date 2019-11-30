#pragma once
#include "Level.h"
#include "Movable_object.h"

class Box : public Movable_object
{
public:
	bool check_collisions(Game_object* collider, int at_x, int at_y, Level &current_level);
	void move_to(char dir, Level &current_level);
};

