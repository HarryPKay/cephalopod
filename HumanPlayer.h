#pragma once
#include "Player.h"

using namespace cephalopod;

/*
 * Player that asks the user to enter input to create the desired moves.
 */
class HumanPlayer final : public Player
{
	/* TYPEDEFS */

	typedef map<Direction, Cell*> Neighbors;

public:

	/* LIFECYCLE */

	HumanPlayer() = delete; /* constructor */
	HumanPlayer(PlayerColor color, GameAnalyzer* gameAnalyzer, BoardModel* boardModel);
	HumanPlayer(const HumanPlayer&) = delete; /* copy */
	HumanPlayer(HumanPlayer&&) = delete; /* move */
	~HumanPlayer() = default; /* destructor */

	/* OPERATORS */

	HumanPlayer& operator=(const HumanPlayer&) = delete; /* copy assignment */
	HumanPlayer& operator=(HumanPlayer&&) = delete; /* move assignment */

	/* METHODS */

	/*
	 * Prompts the user to enter the desired row, column and if available, 
	 * captures.
	 * 
	 * @return A valid move.
	 * 
	 * Post-condition:
	 * - The board state remains unchanged.
	 */
	Move promptForMove() override;

private:

	/* METHODS */

	/*
	 * Shows the available captures available and prompts the user to select 1.
	 * 
	 * @param moves The vector for which there are captures.
	 * @return The index of moves which has the desired capture.
	 * 
	 * Pre-condition:
	 * - The vector of moves all contain the same position.
	 * - The size of the moves is non zero.
	 */
	uint32_t promptForCaptureSelection(const vector<Move>& moves) const;

	/*
	 * Prompts the user to input integers for the row and column for which they
	 * would like to occupy.
	 * 
	 * @return The position created from the user input.
	 */
	Position promptForPosition() const;

	/* DATA MEMBERS */
	BoardModel* board_{};
};
