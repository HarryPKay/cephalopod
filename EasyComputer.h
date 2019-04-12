#pragma once
#include "Common.h"
#include "Player.h"

using namespace cephalopod;

/*
 * A player that moves and captures randomly.
 */
class EasyComputer final : public Player
{
public:

	/* LIFECYCLE */

	EasyComputer() = delete; /* constructor */
	EasyComputer(PlayerColor playerColor, GameAnalyzer* gameAnalyzer);
	EasyComputer(const EasyComputer&) = delete; /* copy */
	EasyComputer(EasyComputer&&) = delete; /* move */
	~EasyComputer() = default; /* destructor */

	/* OPERATORS */

	EasyComputer& operator=(const EasyComputer&) = delete; /* copy assignment */
	EasyComputer& operator=(EasyComputer&&) = delete; /* move assignment */

	/* METHODS */

	Move promptForMove() override;
};
