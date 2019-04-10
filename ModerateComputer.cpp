#include "ModerateComputer.h"



ModerateComputer::ModerateComputer(Color color, BoardModel * board)
	: Player(color, board)
{
}


Move ModerateComputer::promptForMove()
{
	auto moves = board_->findAllPossibleMoves(color_);
	map<int, Move> pipMoveMap;

	// Assign the capture pip value for each move.
	for (const auto& move : moves)
	{
		int key = board_->sumPipForMove(move);
		pipMoveMap[key] = move;
	}

	// Prioritize the highest pip value.
	const auto key = pipMoveMap.rbegin()->first;

	// If there are no captures, move randomly
	if (key == 0)
	{
		const int index = rand() % moves.size();
		return moves[index];
	}

	return pipMoveMap[key];
}