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
	BestMove minimax(BoardModel * board, int depth, Color playerColor, const Move & bestMove);
	BoardModel *board;
	int evaluate(BoardModel* board);

	// temp;
	BoardViewer* boardViewer;
};

