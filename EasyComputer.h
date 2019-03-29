#pragma once
#include "Common.h"
#include "Helpers.h"
#include "Player.h"

using namespace cephalopod;

class EasyComputer :
	public Player
{
public:

	EasyComputer(Color color, BoardModel* board);
	~EasyComputer();
	Move getMove();
};

