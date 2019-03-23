#pragma once
#include <iostream>
#include <stdint.h>
#include <string>
#include "Constants.h"
#include "Player.h"

using namespace cephalopod;

class HumanPlayer :
	public Player
{
public:
	HumanPlayer();
	~HumanPlayer();
	Move getMove();
};

