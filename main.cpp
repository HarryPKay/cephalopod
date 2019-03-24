#include <iostream>
#include <time.h>
#include "GameController.h"

int main()
{
	GameController game;
	game.run();

	cout << "Enter in any input to exit.\n>";
	char keepOpen;
	std::cin >> keepOpen;
	return 0;
}