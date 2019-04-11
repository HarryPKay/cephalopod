#include "Player.h"
#include "Helpers.h"

Player::Player(const PlayerColor playerColor, GameAnalyzer* gameAnalyzer)
	: playerColor_(playerColor)
	  , gameAnalyzer_(gameAnalyzer)
{
	oppositionColor_ = findOpposition(playerColor);
}

PlayerColor Player::getPlayerColor() const
{
	return playerColor_;
}
