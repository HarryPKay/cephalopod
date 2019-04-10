/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other student’s work or from any other source. No part of the code
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

#include "GameController.h"
#include <iostream>

int main (int argc, char *argv[] )
{
	if (argc > 1)
	{
		cout << "Program does not take arguments\n";
		return  EXIT_FAILURE;
	}

	auto selection = 0;
	while (selection == 0) {
		GameController game;
		game.run();
		cout << "Play again?.\n\n";
		cout << "1) Yes\n\n> ";
		std::cin >> selection;
		--selection;
	}

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */