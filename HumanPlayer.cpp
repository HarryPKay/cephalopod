#include "HumanPlayer.h"
#include "Helpers.h"
#include <iomanip>
#include <iostream>

HumanPlayer::HumanPlayer(Color color, BoardModel * board)
	: Player(color, board)
{
}


void HumanPlayer::displayCaptureSelections(const vector<Move>& moves) const
{
	// Nothing to do as there is only one selection.
	if (moves.size() == 1)
	{
		return;
	}

	auto neighbors = board_->getNeighbors(moves[0].position);

	cout << "\nSelect one of the following capture options\n\n";
	
	for (auto i = 0; i < moves.size(); ++i)
	{
		cout << std::setw(2) << i + 1 << ") Neighbors: ";

		auto move = moves[i];

		auto pipSum = 0;
		for (auto captureDirection : move.captureDirections)
		{
			const auto neighbor = neighbors[captureDirection];

			cout << directionEnumToString(captureDirection) << "("
				<< neighbor->getPip() << "), ";
			pipSum += neighbor->getPip();
		}

		cout << "Pip Sum = " << pipSum << "\n";
	}
	cout << "\n> ";
}

Position HumanPlayer::promptForPosition() const
{
	Position position = { -1,-1 };

	do
	{
		cout << "Enter in row and col. e.g: \"1 2\"\n> ";
		cin >> position.row >> position.col;
		--position.row;
		--position.col;
	} while (!board_->isCellVacant(position));

	return position;
}

Move HumanPlayer::promptForMove()
{
	const auto position = promptForPosition();
	auto moves = board_->findPossibleMoves(color_, position);

	// There is only one possible move, no need to prompt for selection;
	if (moves.size() == 1)
	{
		return moves[0];
	}

	auto isValidInput = false;
	auto selection = 0;

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