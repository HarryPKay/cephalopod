#include "ModerateComputer.h"



ModerateComputer::ModerateComputer(Color color, BoardModel * board)
	: Player(color, board)
{
}


ModerateComputer::~ModerateComputer()
{
}

Move ModerateComputer::getMove()
{
	vector<Move> moves = board->getAllPossibleMoves(color);
	map<int, Move> pipMoveMap;

	// Assign the capture pip value for each move.
	for (Move move : moves)
	{
		int key = board->sumPipForMove(move);
		pipMoveMap[key] = move;
	}

	// Prioritize the highest pip value.
	int key = pipMoveMap.rbegin()->first;

	// If there are no captures, move randomly
	if (key == 0)
	{
		int index = rand() % moves.size();
		return moves[index];
	}

	return pipMoveMap[key];
}