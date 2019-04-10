#include "EasyComputer.h"



EasyComputer::EasyComputer(Color color, BoardModel * board)
	: Player(color, board)
{
}

EasyComputer::~EasyComputer()
{
}

Move EasyComputer::getMove()
{
	vector<Move> potentialMoves = board->findAllPossibleMoves(color);
	int index = rand() % potentialMoves.size();
	return potentialMoves[index];
}
