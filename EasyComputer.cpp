#include "EasyComputer.h"

EasyComputer::EasyComputer(const PlayerColor playerColor, BoardModel* board)
	: Player(playerColor, board)
{
}

Move EasyComputer::promptForMove()
{
	auto potentialMoves = board_->findAllPossibleMoves(playerColor_);
	const uint32_t index = rand() % potentialMoves.size();
	return potentialMoves[index];
}
