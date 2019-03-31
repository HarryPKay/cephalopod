#include <iostream>
#include "GameController.h"
#include "HardComputer.h"
#include "Helpers.h"

#include <algorithm>

int main()
{
	int selection = 0;
	while (selection == 0)
	{
		GameController game;
		game.run();
		cout << "Play again?.\n\n";
		cout << "1) Yes\n\n> ";
		std::cin >> selection;
		--selection;
	}
	
	//vector<Captures> potentialTargets = generateCombinationsVaryingSize(directions, 2, 4);

	//for (int i = 0; i < potentialTargets.size(); ++i)
	//{
	//	Captures temp = potentialTargets[i];
	//	for (int j = 0; j < temp.size(); ++j)
	//	{
	//		cout << temp[j] << " ";
	//	}
	//	cout << endl;
	//}

	return 0;
}