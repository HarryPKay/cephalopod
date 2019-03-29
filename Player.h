#pragma once
#include "BoardModel.h"
#include "Common.h"
#include "Move.h"

using namespace cephalopod;

class Player
{
public:
	Player(Color color);
	virtual ~Player();
	Color color;
	virtual Move getMove() = 0;
};

