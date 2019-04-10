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
	HumanPlayer(Color color, BoardModel* board);
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
	void displayCaptureSelections(const vector<Move>& moves) const;
	Position promptForPosition() const;
}; /* -----  end of class HumanPlayer  ----- */
