#include "HumanPlayer.h"
#include "Helpers.h"


HumanPlayer::HumanPlayer(Color color, BoardModel * board)
	: Player(color, board)
{
}

HumanPlayer::~HumanPlayer()
{
}

void HumanPlayer::displayCaptureSelections(const vector<Move>& moves)
{
	// Nothing to do as there is only one selection.
	if (moves.size() == 1)
	{
		return;
	}

	Neighbors neighbors = board->getNeighbors(moves[0].position);

	cout << "\nSelect one of the following capture options\n\n";

	for (int i = 0; i < moves.size(); ++i)
	{
		cout << std::setw(2) << i + 1 << ") Neighbors: ";

		Move move = moves[i];

		int pipSum = 0;
		for (int j = 0; j < move.captureDirections.size(); ++j)
		{
			Direction captureDirection = move.captureDirections[j];
			Cell* neighbour = neighbors[captureDirection];

			cout << directionEnumToString(captureDirection) << "("
				<< neighbour->getPip() << "), ";
			pipSum += neighbour->getPip();
		}

		cout << "Pip Sum = " << pipSum << "\n";
	}
	cout << "\n> ";
}

Position HumanPlayer::promptForPosition()
{
	Position position = { -1,-1 };

	do
	{
		cout << "Enter in row and col. e.g: \"1 2\"\n> ";
		cin >> position.row >> position.col;
		--position.row;
		--position.col;
	} while (!board->isCellVacant(position));

	return position;
}

Move HumanPlayer::promptForMove()
{
	Position position = promptForPosition();
	vector<Move> moves = board->getPossibleMoves(color, position);

	// There is only one possible move, no need to prompt for selection;
	if (moves.size() == 1)
	{
		return moves[0];
	}

	bool isValidInput = false;
	int selection = 0;

	while (!isValidInput)
	{
		displayCaptureSelections(moves);
		cin >> selection;
		--selection;

		if (selection < 0 || selection >= moves.size())
		{
			cout << "Invalid selection\n";
		}
		else
		{
			isValidInput = true;
		}
	}

	return moves[selection];
}

Move HumanPlayer::getMove()
{
	return promptForMove();
}