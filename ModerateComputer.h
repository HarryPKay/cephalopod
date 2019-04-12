#pragma once
#include "Player.h"

/*
 * A player that has a basic strategy of playing greedy. 
 */
class ModerateComputer final : public Player
{
public:

	/* LIFECYCLE */

	ModerateComputer() = delete; /* constructor */
	ModerateComputer(PlayerColor playerColor, GameAnalyzer* gameAnalyzer);
	ModerateComputer(const ModerateComputer&) = delete; /* copy */
	ModerateComputer(ModerateComputer&&) = delete; /* move */
	~ModerateComputer() = default; /* destructor */

	/* OPERATORS */

	ModerateComputer& operator=(const ModerateComputer&) = delete; /* copy assignment */
	ModerateComputer& operator=(ModerateComputer&&) = delete; /* move assignment */

	/* METHODS */

	/*
	 * Find a move that prioritizes gaining the highest pip for the current board
	 * state. If there are no captures, a random move will be found instead.
	 * 
	 * Post-condition:
	 * - The board state does not change.
	 * 
	 * @return A valid move.
	 */
	Move promptForMove() override;
};
