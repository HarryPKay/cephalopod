#include "HumanPlayer.h"
#include "Helpers.h"
#include <iomanip>
#include <iostream>

HumanPlayer::HumanPlayer(const PlayerColor color, GameAnalyzer* gameAnalyzer, BoardModel* boardModel)
	: Player(color, gameAnalyzer), board_(boardModel)
{
}

uint32_t HumanPlayer::promptForCaptureSelection(const vector<Move>& moves) const
{
	cout << "\nSelect one of the following capture options\n\n";

	gameAnalyzer_->printPossibleCaptures(moves);

	uint32_t selection = 0;

	do
	{
		promptForInteger(selection);
		--selection;

		if (selection < 0 || selection >= moves.size())
		{
			cout << "Invalid selection.\n> ";
		}
	}
	while (selection < 0 || selection >= moves.size());

	return selection;
}

Position HumanPlayer::promptForPosition() const
{
	Position position = {0, 0};

	do
	{
		cout << "\nEnter in row and column. e.g: \"1 2\"\n> ";

		promptForInteger(position.row, position.col);

		--position.row;
		--position.col;

		if (!board_->isCellVacant(position))
		{
			cout << "That position is not valid.\n";
		}
	}
	while (!board_->isCellVacant(position));

	return position;
}

Move HumanPlayer::promptForMove()
{
	const auto position = promptForPosition();
	auto moves = gameAnalyzer_->findPossibleMoves(playerColor_, position);

	// There is only one possible move, no need to prompt for selection;
	if (moves.size() == 1)
	{
		return moves[0];
	}

	const auto selection = promptForCaptureSelection(moves);
	return moves[selection];
}
