#pragma once
#include "Common.h"

using namespace cephalopod;

class Player
{
public:
	Player(Color color)
		:color(color) {};
	virtual ~Player();
	Color color;
	virtual Move getMove() = 0;
};

