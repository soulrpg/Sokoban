#include "Level.h"
#include "Game_manager.h"


Level::Level()
{
	Level::moves = 0;
	Level::cursor_x = 0;
    Level::cursor_y = 0;
	Level::mem_cursor_x = 0;
	Level::mem_cursor_y = 0;
	Level::map_of_objects = new Game_object**[15];
	for (int i = 0; i < 15; i++)
	{
		Level::map_of_objects[i] = new Game_object*[15];
	}
}


void Level::set_field(int field_x, int field_y, char s)
{
	switch (s)
	{
	case '#':
		Level::map_of_objects[field_x][field_y] = new Game_object(field_x, field_y, char(219));
		break;
	case 'O':
		Level::map_of_objects[field_x][field_y] = new Game_object(field_x, field_y, ' ');
		break;
	case 'X':
		Level::map_of_objects[field_x][field_y] = new Movable_object(field_x, field_y, char(207), 'W');
		break;
	case '@':
		Level::map_of_objects[field_x][field_y] = new Movable_object(field_x, field_y, '@', 'W');
		break;
	case 'L':
		Level::map_of_objects[field_x][field_y] = new Game_object(field_x, field_y, ' ');
		Level::add_to_storage_vector(field_x, field_y);
		break;
	default:
		//std::cout << s << std::endl;
		throw "Nie znany znak w pliku!";
	}
}

Game_object* Level::get_field(int field_x, int field_y)
{
	return (Game_object*)Level::map_of_objects[field_x][field_y];
}

Game_object* Level::search_for_player()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (map_of_objects[i][j]->get_symbol() == char(64))
			{
				return map_of_objects[i][j];
			}
		}
	}
}

void Level::set_moves(int m)
{
	Level::moves = m;
}

int Level::get_moves()
{
	return Level::moves;
}

// Funkcja przemieszcza kursor w konsoli wykorzystuj¹c funkcjê SetConsoleCursorPosition(HANDLE, COORD) z biblioteki Windows.h.
void Level::move_cursor(int new_x, int new_y)
{
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = new_x;
	coord.Y = new_y;
	SetConsoleCursorPosition(hout, coord);
}

void Level::cursor_back()
{
	Level::move_cursor(Level::mem_cursor_x, Level::mem_cursor_y);
}

void Level::clear_field(int clr_x, int clr_y)
{
	Level::move_cursor(clr_x, clr_y);
	std::cout << " ";
}

void Level::draw_level()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Level::get_field(j, i)->draw();
		}
		std::cout << std::endl;
	}
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hout, &cbsi);
	COORD mem_pos = cbsi.dwCursorPosition;
	Level::mem_cursor_x = mem_pos.X;
	Level::mem_cursor_y = mem_pos.Y;
	std::cout << std::endl;
	std::cout << "Moves: " << Level::moves << std::endl;
	std::cout << "[S]ave state | [Q]uit | [Arrows] - Move ";
}

void Level::clear_screen()
{
	system("CLS");
}

void Level::game_input(Game_manager &game_manager)
{
	char player_input = ' ';
	bool was_saving = false;
	bool level_won = false;
	Game_object *player;
	Level::clear_screen();
	Level::draw_level();
	Level::has_won();
	while (player_input != 'Q' && player_input != 'q')
	{
		std::cin.sync();
		std::cin.clear();
		player_input = _getch();
		if (int(player_input) == -32 || int(player_input) == 0)
		{
			player_input = _getch();
			Level::moves++;
			//std::cout << "p: " << int(player_input) << std::endl;
			switch (int(player_input))
			{
			case 80:
				player = Level::search_for_player();
				((Movable_object*)player)->move_to('S', *this);
				break;
			case 75:
				player = Level::search_for_player();
				((Movable_object*)player)->move_to('A', *this);
				break;
			case 77:
				player = Level::search_for_player();
				((Movable_object*)player)->move_to('D', *this);
				break;
			case 72:
				player = Level::search_for_player();
				((Movable_object*)player)->move_to('W', *this);
				break;
			}
			// Tutaj trzeba jeszcz w pêtli przejœæ po wszystkich Storage_location i narysowaæ je na nowo, poniewa¿ aktualizacja ich nie jest
			// powi¹zana z ruchem. Musi to siê staæ na koñcu!
			if (Level::has_won())
			{
				level_won = true;
				// Tutaj kod, który ma za zadanie powrót do menu chyba i wyœwietlenie gratulacji !
			}
			was_saving = false;
		}
		else
		{
			player_input = (player_input > 90 ? player_input - 32 : player_input);
			if (player_input == 'S')
			{
				try
				{
					was_saving = true;
					game_manager.save_state();
				}
				catch (std::string e)
				{
					std::cout << e << std::endl;
				}

			}
		}
		Level::cursor_back();
		std::cout << std::endl;
		std::cout << "Moves: " << Level::moves << std::endl;
		std::cout << "[S]ave state | [Q]uit | [Arrows] - Move ";
		if (was_saving)
		{
			std::cout << std::endl;
			std::cout << "Game saved." << std::endl;
		}
		if (level_won)
		{
			std::cout << std::endl;
			std::cout << "Level completed! Congratulations!" << std::endl;
		}
	}
	Level::clear_screen();
	game_manager.main_menu();
}

bool Level::has_won()
{
	int filled_storages = 0;
	for (int i = 0; i < Level::storage.size(); i++)
	{
		if (Level::get_field(Level::storage[i].get_pos_x(), Level::storage[i].get_pos_y())->get_symbol() == char(207))
		{
			Level::storage[i].set_filled();
			filled_storages++;
		}
		else
		{
			Level::storage[i].unset_filled();
		}
		Level::move_cursor(Level::storage[i].get_pos_x(), Level::storage[i].get_pos_y());
		if (Level::storage[i].get_pos_x() == Level::search_for_player()->get_pos_x() && Level::storage[i].get_pos_y() == Level::search_for_player()->get_pos_y())
		{
			Level::storage[i].draw(true);
		}
		else
		{
			Level::storage[i].draw(false);
		}
	}
	if (Level::storage.size() == filled_storages)
	{
		return true;
	}
	return false;
}

void Level::add_to_storage_vector(int field_x, int field_y)
{
	Level::storage.push_back(Storage_location(field_x, field_y, 'L'));
}

std::vector<Storage_location> Level::get_storage_vector()
{
	return storage;
}