#include <iostream>
#include "GameController.h"
#include "HardComputer.h"
#include "Helpers.h"

#include <algorithm>

int main()
{
	GameController game;
	game.run();

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

	cout << "Enter in any input to exit.\n>";
	char keepOpen;
	std::cin >> keepOpen;
	return 0;
}