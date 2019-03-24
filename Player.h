#pragma once
#include "BoardModel.h"
#include "Common.h"

using namespace cephalopod;

class Player
{
public:
	Player(Color color);
	virtual ~Player();
	Color color;
	virtual Move getMove() = 0;
	vector<Move> generatePossibleMoves(BoardModel* state);
	vector<vector<Direction>> allPossibleCaptures;
};

