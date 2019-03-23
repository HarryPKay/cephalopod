#pragma once
#include "Common.h"

using namespace cephalopod;

class Player
{
public:
	Player();
	virtual ~Player();
	Color color;
	virtual Move getMove() = 0;
};

