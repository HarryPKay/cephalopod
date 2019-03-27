#pragma once
#include <math.h>
#include "BoardViewer.h"
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
	MoveWithScore minimax(int depth, Color playerColor, const Move & prevMove);
	BoardModel *board;
	float evaluate(BoardModel* board);
};

