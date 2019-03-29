#pragma once
#include "BoardModel.h"
#include "Common.h"
#include "Move.h"

using namespace cephalopod;

class Player
{
public:

	Player(Color color, BoardModel* board);
	virtual ~Player();
	Color color;
	Color getColor();
	BoardModel* board;
	virtual Move getMove() = 0;
};

