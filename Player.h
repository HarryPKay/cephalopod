#pragma once
#include "Color.h"
#include "Move.h"

class Player
{
public:
	Player();
	virtual ~Player();
	Color color;
	virtual Move getMove() = 0;
};

