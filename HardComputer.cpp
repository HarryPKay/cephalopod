#include "HardComputer.h"



HardComputer::HardComputer(Color color, BoardModel * board)
	: Player(color), board(board)
{
	boardViewer = new BoardViewer(board);
}

HardComputer::~HardComputer()
{
}

Move HardComputer::getMove()
{
	Move move = { Position(0, 0), color, vector<Direction>() };
	BestMove bestMove = minimax(board, 3, color, move);
	return bestMove.move;
}

BestMove HardComputer::minimax(BoardModel * board, int depth, Color playerColor, const Move & prevMove)
{
	Color opposition = findOpposition(playerColor);
	BestMove bestMove = { {Position(0, 0), playerColor, vector<Direction>() }, 0 };

	if (playerColor == color)
	{
		bestMove.score = pow(board->getRowCount(),3);
	}
	else
	{
		bestMove.score = -pow(board->getRowCount(), 3);
	}

	if (depth == 0 || board->isBoardFull())
	{
		bestMove.score = evaluate(board);
		return bestMove;
	}

	vector<Move> moves = generatePossibleMoves(board, playerColor);

	for (Move move : moves)
	{
		int score = 0;
		board->setMove(move);
		score = minimax(board, depth - 1, opposition, move).score;
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

int HardComputer::evaluate(BoardModel * board)
{
	int whiteCount = board->getTotalColorCount(white);
	int blackCount = board->getTotalColorCount(black);

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
