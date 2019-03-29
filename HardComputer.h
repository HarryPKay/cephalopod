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
	HardComputer(Color color, BoardModel* board, AIAlgorithm algorithmType, int depth);
	~HardComputer();
private:
	Move getMove();
	float minimax(int depth, Color playerColor, Move & bestMove, bool isFirstIteration);
	float alphabeta(int depth, float alpha, float beta, Color playerColor, Move & bestMove, bool isFirstIteration);
	BoardModel *board;
	float evaluate(BoardModel* board);
	AIAlgorithm algorithmType;
	int depth;
};

