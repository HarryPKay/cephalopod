#pragma once
//#include <algorithm>
#include "Board.h"
#include "Helpers.h"
#include "Player.h"

using namespace cephalopod;

class RandomPlayer :
	public Player
{
public:
	RandomPlayer(Color color, Board* board)
		: Player(color), board(board) {};
	~RandomPlayer();
	Board* board;
	Move getMove();
};

