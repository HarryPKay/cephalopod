#pragma once
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <string>
#include "Player.h"

using namespace cephalopod;

class HumanPlayer :
	public Player
{
public:

	typedef map<Direction, Cell*> Neighbours;

	HumanPlayer(Color color, BoardModel* board);
	~HumanPlayer();
	void displayCaptureSelections(const vector<Move>& moves);
	Position promptForPosition();
	Move promptForMove();
	Move getMove();
};

