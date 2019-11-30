#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include "Game_object.h"
#include "Movable_object.h"
#include "Storage_location.h"
//#include "Game_manager.h"

////////////////////////
// Ta klasa okreœla poziom w ca³oœci, przechowuje obiekty gry w polu map_of_objects, iloœæ ruchów jakie gracz wykona³ na danym
// poziomie oraz x i y pola w konsoli na które aktualnie wskazuje kursor. Ma funkcjê do odczytywania inputu gracza, przemieszczania kursora
// po konsoli i sprawdzania warunku zwyciêstwa.
////////////////////////

class Game_manager;

class Level
{
private:
	int moves;
	int cursor_x;
	int cursor_y;
	int mem_cursor_x;
	int mem_cursor_y;
	Game_object*** map_of_objects;
	std::vector<Storage_location> storage;
public:
	Level();
	void set_field(int field_x, int field_y, char s);
	Game_object* get_field(int field_x, int field_y);
	Game_object* search_for_player();
	void set_moves(int m);
	int get_moves();
	void move_cursor(int new_x, int new_y);
	void cursor_back();
	void clear_field(int clr_x, int clr_y);
	void draw_level();
	void clear_screen();
	void game_input(Game_manager &game_manager);
	bool has_won();
	void add_to_storage_vector(int field_x, int field_y);
	std::vector<Storage_location> get_storage_vector();
};

