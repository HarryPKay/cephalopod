#include "ModerateComputer.h"

ModerateComputer::ModerateComputer(PlayerColor playerColor, BoardModel* board)
	: Player(playerColor, board)
{
}

Move ModerateComputer::promptForMove()
{
	auto moves = board_->findAllPossibleMoves(playerColor_);
	map<int, Move> pipMoveMap;

	// Assign the capture pip value for each available move.
	for (const auto& move : moves)
	{
		auto key = board_->sumPipForMove(move);
		pipMoveMap[key] = move;
	}

	// Prioritize the highest pip value.
	const auto key = pipMoveMap.rbegin()->first;

	// If there are no captures, move randomly
	if (key == 0)
	{
		const uint32_t index = rand() % moves.size();
		return moves[index];
	}

	return pipMoveMap[key];
}
