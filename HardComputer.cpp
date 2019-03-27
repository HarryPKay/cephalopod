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
	Move move = { Position(0, 0), color, Capture() };
	minimax(3, color, move, true);
	return move;
}

float HardComputer::minimax(int depth, Color playerColor, Move & bestMove, bool isFirstIteration)
{
	map<float, Move> evaluatedMoves;
	Color opposition = board->findOpposition(playerColor);
	
	if (depth == 0 || board->isBoardFull())
	{
		return evaluate(board);
	}

	vector<Move> moves = board->getPossibleMoves(playerColor);

	if (playerColor == color)
	{
		float score = -1 * board->getRowCount() * board->getColCount();

		for (Move move : moves)
		{
			board->setMove(move);
			float temp = minimax(depth - 1, opposition, bestMove, false);

			if (isFirstIteration && temp > score)
			{
				score = temp;
				bestMove = move;
			}
			board->undoMove();
		}

		return score;
	}
	else
	{
		float score = board->getRowCount() * board->getColCount();

		for (Move move : moves)
		{
			board->setMove(move);
			score = max(minimax(depth - 1, opposition, bestMove, false), score);
			board->undoMove();
		}

		return score;
	}
}

float HardComputer::evaluate(BoardModel * board)
{
	// Should we add points if it can score a six
	float whiteCount = board->getTotalColorCount(white);
	float blackCount = board->getTotalColorCount(black);

	if (color == white)
	{
		return whiteCount - blackCount;
	}
	else
	{
		return blackCount - whiteCount;
	}
	return 0;
}
