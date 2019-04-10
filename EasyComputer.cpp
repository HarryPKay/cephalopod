#include "EasyComputer.h"

EasyComputer::EasyComputer(const Color color, BoardModel* board)
	: Player(color, board)
{
}

Move EasyComputer::promptForMove()
{
	auto potentialMoves = board_->findAllPossibleMoves(color_);
	const int index = rand() % potentialMoves.size();
	return potentialMoves[index];
}
