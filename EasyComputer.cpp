#include "EasyComputer.h"



EasyComputer::~EasyComputer()
{
}

Move EasyComputer::getMove()
{
	vector<Move> potentialMoves = board->getPossibleMoves(color);
	return potentialMoves[rand() % potentialMoves.size()];
}
