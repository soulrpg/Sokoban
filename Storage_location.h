#pragma once
#include <Windows.h>
//#include "Level.h"
#include "Game_object.h"

////////////////////////
// Storage_location to zwyk³y obiekt, który nie mo¿e siê poruszaæ z t¹ ró¿nic¹, ¿e ma pole is_filled, które okreœla czy znajduje siê na nim
// jakaœ skrzynka. Oprócz tego nadpisuje funkcjê draw() z tego wzglêdu, ¿e w przypadku Storage_location nie bêdzie wyœwietlany zwyk³y znak w
// konsoli, lecz t³o miejsca na którym ma siê znajdowaæ pusty znak bêdzie pokolorowane na inny kolor.
////////////////////////

class Storage_location : public Game_object
{
private:
	bool is_filled;
public:
	Storage_location(int x, int y, char s);
	//bool check_if_filled(Level &current_level);
	void set_filled();
	void unset_filled();
	void draw(bool player_on);
};

