#pragma once
#include "Player.h"

using namespace cephalopod;

/*
 * =====================================================================================
 *        Class:  HumanPlayer
 *  Description:  
 *
 * =====================================================================================
 */
class HumanPlayer final : public Player
{
	typedef map<Direction, Cell*> Neighbors;

public:
	/* ====================  LIFECYCLE     ======================================= */
	HumanPlayer() = delete; /* constructor */
	HumanPlayer(PlayerColor color, GameAnalyzer* gameAnalyzer, BoardModel* boardModel);
	~HumanPlayer() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	HumanPlayer(const HumanPlayer&) = delete; /* copy */
	HumanPlayer(HumanPlayer&&) = delete; /* move */

	/* ====================  OPERATORS     ======================================= */
	HumanPlayer& operator=(const HumanPlayer&) = delete; /* copy assignment */
	HumanPlayer& operator=(HumanPlayer&&) = delete; /* move assignment */

	/* ====================  METHODS       ======================================= */
	Move promptForMove() override;

private:
	/* ====================  METHODS       ======================================= */
	uint32_t promptForCaptureSelection(const vector<Move>& moves) const;
	Position promptForPosition() const;
	BoardModel* board_{};
}; /* -----  end of class HumanPlayer  ----- */
