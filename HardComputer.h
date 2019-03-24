#pragma once
#include "Common.h"
#include "Player.h"

using namespace std;
using namespace cephalopod;

class HardComputer :
	public Player
{
public:
	HardComputer(Color color, BoardModel* board);
	~HardComputer();
private:
	Move getMove();
	Move Minimax(BoardModel* board, int depth, Color color);
	BoardModel *board;
	int evaluate(BoardModel* board);
};

