#include "Game_manager.h"
#include "Game_object.h"
#include "Movable_object.h"
#include "Storage_location.h"

Game_manager::Game_manager(int max_levels) {
	Game_manager::choice = ' ';
	Game_manager::level_load_id = 0;
	Game_manager::number_of_levels = max_levels;
	main_menu();
}

// Funkcja zajmujaca sie komunikacja z uzytniownikiem, umozliwia wybor opcji z menu
void Game_manager::main_menu()
{
	while (true)
	{
		Game_manager::choice = '3';
		Game_manager::level_load_id = 0;
		while (choice <= '0' || choice > '2')
		{
			std::cout << "#####################" << std::endl;
			std::cout << "###### Sokoban ######" << std::endl;
			std::cout << "#####################" << std::endl;
			std::cout << "Wybierz opcje: " << std::endl;
			std::cout << "1) Wybierz dany poziom, 2) Wczytaj stan ostatniej gry, 3) Wyjdz z programu." << std::endl;
			std::cout << "Wybor:";
			std::cin >> choice;
		}
		try {
			switch (choice)
			{
			case '1':
				while (level_load_id <= 0 || level_load_id > Game_manager::number_of_levels)
				{
					std::cout << "Podaj numer poziomu (1-" << Game_manager::number_of_levels << ").: ";
					std::cin.sync();
					std::cin.clear();
					std::cin >> level_load_id;
				}
				Game_manager::current_level = Game_manager::load_level();
				Game_manager::current_level.game_input(*this);
				break;
			case '2':
				Game_manager::current_level = Game_manager::load_state();
				Game_manager::current_level.game_input(*this);
				break;
			case '3':
				exit(0);
			}
		}
		catch (const char* e)
		{
			std::cout << e << std::endl;
			_getch();
		}

	}
}

// Funkcja wczytujaca poziom z pliku txt, zwraca Level
Level Game_manager::load_level()
{
	std::ifstream file_to_read;
	std::string file_name = "poziom" + std::to_string(Game_manager::level_load_id) + ".txt";
	std::cout << file_name << std::endl;
	file_to_read.open(file_name.c_str());
	if (!file_to_read.good())
	{
		throw "Blad otwarcia pliku!";
		Game_manager::main_menu();
	}
	Level temporary;
	int row = 0;
	int column = 0;
	char s;
	file_to_read >> s;
	while (!file_to_read.eof())
	{
		temporary.set_field(column, row, s);
		if (column == 14)
		{
			column = 0;
			row++;
		}
		else
		{
			column++;
		}
		file_to_read >> s;
	}
	file_to_read.close();
	if (row <= 14 && column < 14)
	{
		throw "Zla struktura pliku!";
	}
	return temporary;
}

// Funkcja wczytujaca stan gry z pliku txt, zwraca lekko zmodyfikowany obiekt klasy Level
Level Game_manager::load_state()
{
	std::ifstream file_to_read;
	file_to_read.open("zapis.txt");
	if (!file_to_read.good())
	{
		throw "Blad otwarcia pliku!";
	}
	Level temporary;
	int row = 0;
	int column = 0;
	char s;
	std::vector<char> tmp;
	file_to_read >> s;
	while (!file_to_read.eof())
	{
		if (row == 15)
		{
			tmp.push_back(s);
		}
		else
		{
			temporary.set_field(column, row, s);
		}
		if (column == 14)
		{
			column = 0;
			row++;
		}
		else
		{
			column++;
		}
		file_to_read >> s;
		if (!std::cin.good())
		{
			throw "Blad wczytywania z pliku! Bledne dane! ";
		}
	}
	int m = 0;
	for (int i = 0; i < tmp.size(); i++)
	{
		m = m * 10 + int(tmp[i]) - 48;
	}
	temporary.set_moves(m);
	file_to_read.close();
	return temporary;
}

// Zapisuje stan gry do pliku zapis.txt, na plik sk³ada siê stan ca³ej planszy gry oraz licznik iloœci ruchów (ostatni wiersz pliku).
void Game_manager::save_state()
{
	std::ofstream file_to_write;
	file_to_write.open("zapis.txt");
	if (!file_to_write.good())
	{
		throw "Blad zapisu do pliku!";
	}
	char tab[15][15];
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			char s = Game_manager::current_level.get_field(j, i)->get_symbol();
			if (s == char(207))
				tab[j][i] = 'X';
			if (s == char(219))
				tab[j][i] = '#';
			if (s == ' ')
				tab[j][i] = 'O';
			if (s == '@')
				tab[j][i] = '@';
		}
	}
	for (int i = 0; i < Game_manager::current_level.get_storage_vector().size(); i++)
	{
		int x = Game_manager::current_level.get_storage_vector()[i].get_pos_x();
		int y = Game_manager::current_level.get_storage_vector()[i].get_pos_y();
		tab[x][y] = 'L';
	}
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			file_to_write << tab[j][i];
			//if (s == char())
			//file_to_write << Game_manager::current_level.get_field(i, j)->get_symbol();
		}
		file_to_write << std::endl;
	}
	file_to_write << Game_manager::current_level.get_moves();
	file_to_write.close();
}