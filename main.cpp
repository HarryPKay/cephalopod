/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other studentís work or from any other source. No part of the code
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

#include "GameController.h"
#include <iostream>
#include "Helpers.h"

int main()
{
	uint32_t selection = 0;
	do
	{
		GameController game;
		game.run();

		cout << "Play again?.\n\n";
		cout << "1) Yes\n";
		cout << "Any other number for no.\n\n> ";
		promptForInteger(selection);
		--selection;
	}
	while (selection == 0);

	return EXIT_SUCCESS;
}
