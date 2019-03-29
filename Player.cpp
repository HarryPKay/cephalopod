#include "Player.h"


Player::Player(Color color, BoardModel* board)
	: color(color), board(board)
{
}

Player::~Player()
{
}

Color Player::getColor()
{
	return color;
}
