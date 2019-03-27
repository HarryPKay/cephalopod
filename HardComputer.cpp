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
	MoveWithScore bestMove = minimax(3, color, move);
	return bestMove.move;
}

MoveWithScore HardComputer::minimax(int depth, Color playerColor, const Move & prevMove)
{
	Color opposition = board->findOpposition(playerColor);
	MoveWithScore bestMove = { {Position(0, 0), playerColor, Capture() }, 0 };

	if (playerColor == color)
	{
		bestMove.score = INFINITY;
	}
	else
	{
		bestMove.score = -INFINITY;
	}

	if (depth == 0 || board->isBoardFull())
	{
		bestMove.score = evaluate(board);
		return bestMove;
	}

	vector<Move> moves = board->getPossibleMoves(playerColor);

	for (Move move : moves)
	{
		float score = 0;
		board->setMove(move);
		score = minimax(depth - 1, opposition, move).score;
		board->undoMove();
		if (playerColor == color && score < bestMove.score)
		{
			bestMove.score = score;
			bestMove.move = move;	
		}
		else if (playerColor != color && score > bestMove.score)
		{
			bestMove.score = score;
			bestMove.move = move;
		}	
	}

	return bestMove;
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
