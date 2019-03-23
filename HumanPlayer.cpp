#include "HumanPlayer.h"



HumanPlayer::HumanPlayer()
{
}


HumanPlayer::~HumanPlayer()
{
}

Move HumanPlayer::getMove()
{
	std::cout << color << " turn (colNo rowNo isCapture)> ";
	std::string input;
	std::cin >> input;
	std::vector<std::string> splitInput;

	// TODO: put into helper function file
	for (int left = 0, right = 0; right < input.size(); ++right)
	{
		if (input[right] == MOVE_SEPARATOR) {
			splitInput.push_back(input.substr(left, right - left));
			left = right + 1;
		}
	}

	Position position = { std::stoi(splitInput[0]), std::stoi(splitInput[1]) };
	bool isCapture = false;
	// TODO: put as const
	if (splitInput[2] == "t")
	{
		isCapture = true;
	}

	// TODO: validation (post condition)
	return { position, color, isCapture };
}