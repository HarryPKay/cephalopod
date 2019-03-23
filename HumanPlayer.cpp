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
	vector<Direction> captureTargets;
	cout << "Enter capture targets>\n";

	while (captureTarget !=  'f')
	{
		cin >> captureTarget;
		switch (captureTarget)
		{
		case 'u':
			captureTargets.push_back(Direction::up);
			break;
		case 'r':
			captureTargets.push_back(Direction::right);
			break;
		case 'd':
			captureTargets.push_back(Direction::down);
			break;
		case 'l':
			captureTargets.push_back(Direction::left);
			break;
		}
	}

	// TODO: have this prompt only if there are captures available;

	return { Position(row,col), color, captureTargets };
}