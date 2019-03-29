#include "EasyComputer.h"



EasyComputer::~EasyComputer()
{
}

Move EasyComputer::getMove()
{
	vector<Move> potentialMoves = board->getAllPossibleMoves(color);
	return potentialMoves[rand() % potentialMoves.size()];
}
