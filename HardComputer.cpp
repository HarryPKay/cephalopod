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
	//minimax(3, color, move, true);
	alphabeta(9, -INFINITY, INFINITY, color, move, true);
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
		float score = -INFINITY;

		for (Move move : moves)
		{
			board->setMove(move);
			float temp = minimax(depth - 1, opposition, bestMove, false);

			if (temp > score)
			{
				score = temp;
				if (isFirstIteration)
				{
					bestMove = move;
				}
			}
			board->undoMove();
		}

		return score;
	}
	else
	{
		float score = INFINITY;

		for (Move move : moves)
		{
			board->setMove(move);
			score = max(minimax(depth - 1, opposition, bestMove, false), score);
			board->undoMove();
		}

		return score;
	}
}

float HardComputer::alphabeta(int depth, float alpha, float beta, Color playerColor, Move & bestMove, bool isFirstIteration)
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
		float score = -INFINITY;

		for (Move move : moves)
		{
			board->setMove(move);
			float temp = alphabeta(depth - 1, alpha, beta, opposition, bestMove, false);
			board->undoMove();

			alpha = max(alpha, score);

			if (alpha >= beta)
			{
				return score;
			}

			if (temp > score)
			{
				score = temp;
				if (isFirstIteration)
				{
					bestMove = move;
				}
			}
		}

		return score;
	}
	else
	{
		float score = INFINITY;

		for (Move move : moves)
		{
			board->setMove(move);
			score = alphabeta(depth - 1, alpha, beta, opposition, bestMove, false);
			board->undoMove();

			beta = min(beta, score);

			if (alpha >= beta)
			{
				return score;
			}
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
