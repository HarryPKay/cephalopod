#pragma once
#include "Common.h"
#include "Move.h"
#include "GameAnalyzer.h"

using namespace cephalopod;

/*
 * ABSTRACT CLASS
 * 
 * Provides the template for all players to inherit. All players must:
 * - Implement a method to find moves.
 * - A reference to the game rules.
 * - A color.
 */
class Player
{
public:
	/* LIFECYCLE */

	Player() = delete; /* constructor */
	Player(PlayerColor playerColor, GameAnalyzer* gameAnalyzer);
	Player(const Player&) = delete; /* copy */
	Player(Player&&) = delete; /* move */
	virtual ~Player() = default; /* destructor */

	/* OPERATORS  */
	Player& operator=(const Player&) = delete; /* copy assignment */
	Player& operator=(Player&&) = delete; /* move assignment */

	/* ACCESSORS */

	PlayerColor getPlayerColor() const;

	/* METHODS */

	virtual Move promptForMove() = 0;

protected:

	/* DATA MEMBERS */

	PlayerColor playerColor_;
	PlayerColor oppositionColor_;
	GameAnalyzer* gameAnalyzer_;
};
