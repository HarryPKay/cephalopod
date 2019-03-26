#include "EasyComputer.h"



EasyComputer::~EasyComputer()
{
}

Move EasyComputer::getMove()
{
	vector<Move> potentialMoves = generatePossibleMoves(board, color);
	return potentialMoves[rand() % potentialMoves.size()];
}
