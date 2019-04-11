#include "Player.h"
#include "Helpers.h"

Player::Player(const PlayerColor playerColor, BoardModel* board)
	: playerColor_(playerColor)
	  , board_(board)
{
	oppositionColor_ = findOpposition(playerColor);
}

PlayerColor Player::getPlayerColor() const
{
	return playerColor_;
}
