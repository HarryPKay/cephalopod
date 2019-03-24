#pragma once
#include "BoardModel.h"
#include "Common.h"
#include "Helpers.h"
#include "Player.h"

using namespace cephalopod;

class EasyComputer :
	public Player
{
public:
	EasyComputer(Color color, BoardModel* board)
		: Player(color), board(board) {};
	~EasyComputer();
	BoardModel* board;
	Move getMove();
};

