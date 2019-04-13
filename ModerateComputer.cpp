#include "ModerateComputer.h"

ModerateComputer::ModerateComputer(const PlayerColor playerColor, GameAnalyzer* gameAnalyzer)
	: Player(playerColor, gameAnalyzer)
{
}

Move ModerateComputer::promptForMove()
{
	// Assign the capture pip value for each available move.
	auto moves = gameAnalyzer_->findAllValidMoves(playerColor_);
	map<int32_t, Move> pipMoveMap;
	for (const auto& move : moves)
	{
		const auto key = gameAnalyzer_->sumPipForMove(move);
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
