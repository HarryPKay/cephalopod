#pragma once
#include "BoardModel.h"
#include "Player.h"


class HardComputer :
	public Player
{
public:
	HardComputer(Color color)
		: Player(color), board(board) {};
	~HardComputer();
private:
	Move getMove();
	Move Minimax(BoardModel* board, int depth, Color color);
	BoardModel *board;
	int evaluate(BoardModel* board);
};

