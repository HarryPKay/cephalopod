#include "HardComputer.h"



HardComputer::HardComputer(Color color, BoardModel * board)
	: Player(color), board(board)
{
}

HardComputer::~HardComputer()
{
}

Move HardComputer::getMove()
{
	vector<Move> potentialMoves = generatePossibleMoves(board);
	return potentialMoves[0];
	//return Move{ Position(0,0),color,vector<Direction>() };
}

Move HardComputer::Minimax(BoardModel * board, int depth, Color color)
{
	// get the row of the worse for enemy
	// or get hte score of best for this

	// if depth = 0, return row col score

	// for each permutation, setmove, recursively core
	// remove move

	// assign best score

	// return best

	return getMove();
}

int HardComputer::evaluate(BoardModel * board)
{
	if (board->getMajorityColor() == color)
	{
		return 1;
	}
	else if (board->getMajorityColor() == noColor)
	{
		return 0;
	}
	return -1;
}
