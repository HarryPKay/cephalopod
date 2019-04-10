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
	Move getMove() override;
	Move minimax();
	Move alphaBeta();
	float minValue(int depth);
	float maxValue(int depth);
	float minValue(int depth, float alpha, float beta);
	float maxValue(int depth, float alpha, float beta);
	float evaluate() const;
	AIAlgorithm algorithmType;
	int depth;
};

