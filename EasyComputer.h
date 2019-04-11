#pragma once
#include "Common.h"
#include "Player.h"

using namespace cephalopod;

/*
 * =====================================================================================
 *        Class:  EasyComputer
 *  Description:  
 *
 * =====================================================================================
 */
class EasyComputer final : public Player
{
public:
	/* ====================  LIFECYCLE     ======================================= */
	EasyComputer() = delete; /* constructor */
	EasyComputer(PlayerColor playerColor, GameAnalyzer* gameAnalyzer);
	~EasyComputer() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	EasyComputer(const EasyComputer&) = delete; /* copy */
	EasyComputer(EasyComputer&&) = delete; /* move */

	/* ====================  OPERATORS     ======================================= */
	EasyComputer& operator=(const EasyComputer&) = delete; /* copy assignment */
	EasyComputer& operator=(EasyComputer&&) = delete; /* move assignment */

	/* ====================  METHODS       ======================================= */
	Move promptForMove() override;
}; /* -----  end of class EasyComputer  ----- */
