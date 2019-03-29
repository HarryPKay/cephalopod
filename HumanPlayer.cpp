#include "HumanPlayer.h"



HumanPlayer::~HumanPlayer()
{
}

Move HumanPlayer::getMove()
{
	//TODO: validate
	cout << color << "'s turn\n";

	int row;
	cout << "Enter in row coordinate\n>";
	cin >> row;
	--row;

	int col;
	cout << "Enter in column coordinate\n>";
	cin >> col;
	--col;

	char captureTarget = ' ';
	Capture captureDirections;
	cout << "Enter capture targets>\n";

	while (captureTarget !=  'f')
	{
		cin >> captureTarget;
		switch (captureTarget)
		{
		case 'u':
			captureDirections.push_back(Direction::up);
			break;
		case 'r':
			captureDirections.push_back(Direction::right);
			break;
		case 'd':
			captureDirections.push_back(Direction::down);
			break;
		case 'l':
			captureDirections.push_back(Direction::left);
			break;
		}
	}

	// TODO: have this prompt only if there are captures available;

	return { Position(row,col), color, captureDirections };
}