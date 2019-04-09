#include "HardComputer.h"



HardComputer::HardComputer(Color color, BoardModel * board, AIAlgorithm algorithmType, int depth)
	: Player(color, board), algorithmType(algorithmType), depth(depth)
{
}

HardComputer::~HardComputer()
{
}

Move HardComputer::getMove()
{
	Move move = { Position(0, 0), color, Captures() };

	switch (algorithmType)
	{
	case AIAlgorithm::minimax:
		//minimax(depth, color, move, true);
		return minimax();
		break;
	case AIAlgorithm::alphabeta:
		return alphaBeta();
		//alphabeta(depth, -INFINITY, INFINITY, color, move, true);
		break;
	}

	return move;
}

Move HardComputer::minimax()
{
	map<float, Move> valueMoveMap;
	vector<Move> moves = board->getAllPossibleMoves(color);

	for (Move move : moves)
	{
		float value = maxValue(depth);
		valueMoveMap[value] = move;
	}

	// Retrieve the largest key
	float key = valueMoveMap.rbegin()->first;
	return valueMoveMap[key];
}

Move HardComputer::alphaBeta()
{
	map<float, Move> valueMoveMap;
	vector<Move> moves = board->getAllPossibleMoves(color);

	for (Move move : moves)
	{
		float value = maxValue(depth, -INFINITY, INFINITY);
		valueMoveMap[value] = move;
	}

	// Retrieve the largest key
	float key = valueMoveMap.rbegin()->first;
	return valueMoveMap[key];
}

float HardComputer::minValue(int depth)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board->isBoardFull())
	{
		return evaluate();
	}

	// general case: there are board states to search.
	float value = INFINITY;
	vector<Move> moves = board->getAllPossibleMoves(findOpposition(color));

	for (Move move : moves)
	{
		board->setMove(move);
		value = min(value, maxValue(depth - 1));
		board->undoMove();
	}

	return value;
}

float HardComputer::minValue(int depth, float alpha, float beta)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board->isBoardFull())
	{
		return evaluate();
	}

	// general case: there are board states to search.
	float value = INFINITY;
	vector<Move> moves = board->getAllPossibleMoves(findOpposition(color));

	for (Move move : moves)
	{
		board->setMove(move);
		value = min(value, maxValue(depth - 1, alpha, beta));
		board->undoMove();

		if (value <= alpha)
		{
			return value;
		}

		beta = min(beta, value);
	}

	return value;
}

float HardComputer::maxValue(int depth)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board->isBoardFull())
	{
		return evaluate();
	};

	// general case: there are board states to search.
	float value = -INFINITY;
	vector<Move> moves = board->getAllPossibleMoves(color); // This computer's color

	for (Move move : moves)
	{
		board->setMove(move);
		value = max(value, minValue(depth - 1));
		board->undoMove();
	}

	return value;
}

float HardComputer::maxValue(int depth, float alpha, float beta)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board->isBoardFull())
	{
		return evaluate();
	};

	// general case: there are board states to search.
	float value = -INFINITY;
	vector<Move> moves = board->getAllPossibleMoves(color); // This computer's color

	for (Move move : moves)
	{
		board->setMove(move);
		value = max(value, minValue(depth - 1, alpha, beta));
		board->undoMove();

		if (value >= beta)
		{
			return value;
		}

		alpha = max(alpha, value);
	}

	return value;
}

float HardComputer::evaluate()
{
	// Should we add points if it can score a six
	float whiteCount = (float)board->getTotalColorCount(white);
	float blackCount = (float)board->getTotalColorCount(black);

	if (color == white)
	{
		return whiteCount - blackCount;
	}

	return blackCount - whiteCount;
}
