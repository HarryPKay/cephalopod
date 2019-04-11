#pragma once
#include "Player.h"

/*
 * =====================================================================================
 *        Class:  ModerateComputer
 *  Description:  
 *
 * =====================================================================================
 */
class ModerateComputer final : public Player
{
public:
	/* ====================  LIFECYCLE     ======================================= */
	ModerateComputer() = delete; /* constructor */
	ModerateComputer(PlayerColor playerColor, GameAnalyzer* gameAnalyzer);
	~ModerateComputer() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	ModerateComputer(const ModerateComputer&) = delete; /* copy */
	ModerateComputer(ModerateComputer&&) = delete; /* move */

	/* ====================  OPERATORS     ======================================= */
	ModerateComputer& operator=(const ModerateComputer&) = delete; /* copy assignment */
	ModerateComputer& operator=(ModerateComputer&&) = delete; /* move assignment */

	/* ====================  METHODS       ======================================= */
	Move promptForMove() override;
}; /* -----  end of class ModerateComputer  ----- */
