#include "HardComputer.h"



HardComputer::HardComputer(Color color, BoardModel * board)
	: Player(color), board(board)
{
	allPossibleCaptures = generateCombinationsVaryingSize(directions, 2, 4);
	allPossibleCaptures.push_back(vector<Direction>());
}

HardComputer::~HardComputer()
{
}

vector<Move> HardComputer::generatePossibleMoves(BoardModel* state)
{
	vector<Move> potentialMoves;
	Move move = { Position(0,0),color, vector<Direction>() };

	for (int i = 0; i < state->getRowCount(); ++i)
	{
		for (int j = 0; j < state->getColCount(); ++j)
		{	
			move.position = Position(i, j);

			for (int i = 0; i < allPossibleCaptures.size(); ++i)
			{
				move.captureTargets = allPossibleCaptures[i];

				if (state->isMoveValid(move))
				{
					potentialMoves.push_back(move);
				}
			}
		}
	}
	return potentialMoves;
}

Move HardComputer::getMove()
{
	vector<Move> potentialMoves = generatePossibleMoves(board);
	cout << potentialMoves.size() << " size" << "\n";
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
