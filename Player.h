#pragma once
#include "BoardModel.h"
#include "Common.h"
#include "Move.h"

using namespace cephalopod;

/*
 * =====================================================================================
 *        Class:  Player
 *  Description:  
 *
 * =====================================================================================
 */
class Player
{
public:
	/* ====================  LIFECYCLE     ======================================= */
	Player() = delete; /* constructor */
	Player(PlayerColor playerColor, BoardModel* board);
	virtual ~Player() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	Player(const Player&) = delete; /* copy */
	Player(Player&&) = delete; /* move */

	/* ====================  ACCESSORS     ======================================= */
	PlayerColor getPlayerColor() const;

	/* ====================  OPERATORS     ======================================= */
	Player& operator=(const Player&) = delete; /* copy assignment */
	Player& operator=(Player&&) = delete; /* move assignment */

	/* ====================  METHODS       ======================================= */
	virtual Move promptForMove() = 0;

protected:
	/* ====================  DATA MEMBERS  ======================================= */
	PlayerColor playerColor_;
	PlayerColor oppositionColor_;
	BoardModel* board_;
}; /* -----  end of class Player  ----- */
