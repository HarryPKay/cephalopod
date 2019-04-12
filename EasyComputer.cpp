#include "EasyComputer.h"

EasyComputer::EasyComputer(const PlayerColor playerColor, GameAnalyzer* gameAnalyzer)
	: Player(playerColor, gameAnalyzer)
{
}

Move EasyComputer::promptForMove()
{
	// Grab all of the moves and randomly select an index of a move to return.
	auto potentialMoves = gameAnalyzer_->findAllPossibleMoves(playerColor_);
	const uint32_t index = rand() % potentialMoves.size();
	return potentialMoves[index];
}
