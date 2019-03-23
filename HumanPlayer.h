#pragma once
#include <iostream>
#include <stdint.h>
#include <string>
#include "Player.h"

using namespace cephalopod;

class HumanPlayer :
	public Player
{
public:
	HumanPlayer(Color color)
		:Player(color) {};
	~HumanPlayer();
	Move getMove();
};

