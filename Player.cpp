#include "Player.h"


Player::Player(const Color color, BoardModel* board)
	: color_(color), board_(board)
{
}


Color Player::getColor() const
{
	return color_;
}
