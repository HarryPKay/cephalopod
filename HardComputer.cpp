#include "HardComputer.h"
#include "Helpers.h"

HardComputer::HardComputer(
	const Color color,
	BoardModel * board,
	const AIAlgorithm algorithmType,
	const int depth
)
	: Player(color, board), algorithmType_(algorithmType), depth_(depth)
{
}

Move HardComputer::promptForMove()
{
	switch (algorithmType_)
	{
	case AIAlgorithm::minimax:
		return minimax();
	default:
		return alphaBeta();
	}
}

Move HardComputer::minimax()
{
	map<float, Move> valueMoveMap;
	auto moves = board_->findAllPossibleMoves(color_);

	for (const auto& move : moves)
	{
		board_->setMove(move);
		auto value = minValue(depth_ - 1);
		valueMoveMap[value] = move;
		board_->undoMove();
	}

	// Retrieve the largest key
	const float key = valueMoveMap.rbegin()->first;
	return valueMoveMap[key];
}

Move HardComputer::alphaBeta()
{
	map<float, Move> valueMoveMap;
	auto moves = board_->findAllPossibleMoves(color_);

	for (const auto& move : moves)
	{
		board_->setMove(move);
		auto value = minValue(depth_ - 1, -INFINITY, INFINITY);
		valueMoveMap[value] = move;
		board_->undoMove();
	}

	// Retrieve the largest key
	const auto key = valueMoveMap.rbegin()->first;
	return valueMoveMap[key];
}

float HardComputer::minValue(const int depth)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate();
	}

	// general case: there are board states to search.
	auto value = INFINITY;
	auto moves = board_->findAllPossibleMoves(findOpposition(color_));

	for (const auto& move : moves)
	{
		board_->setMove(move);
		value = min(value, maxValue(depth - 1));
		board_->undoMove();
	}

	return value;
}

float HardComputer::minValue(const int depth, const float alpha, float beta)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate();
	}

	// general case: there are board states to search.
	auto value = INFINITY;
	auto moves = board_->findAllPossibleMoves(findOpposition(color_));

	for (const auto& move : moves)
	{
		board_->setMove(move);
		value = min(value, maxValue(depth - 1, alpha, beta));
		board_->undoMove();

		if (value <= alpha)
		{
			return value;
		}

		beta = min(beta, value);
	}

	return value;
}

float HardComputer::maxValue(const int depth)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate();
	};

	// general case: there are board states to search.
	auto value = -INFINITY;
	auto moves = board_->findAllPossibleMoves(color_); // This computer's color

	for (const auto& move : moves)
	{
		board_->setMove(move);
		value = max(value, minValue(depth - 1));
		board_->undoMove();
	}

	return value;
}

float HardComputer::maxValue(const int depth, float alpha, const float beta)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate();
	};

	// general case: there are board states to search.
	auto value = -INFINITY;
	auto moves = board_->findAllPossibleMoves(color_); // This computer's color

	for (const auto& move : moves)
	{
		board_->setMove(move);
		value = max(value, minValue(depth - 1, alpha, beta));
		board_->undoMove();

		if (value >= beta)
		{
			return value;
		}

		alpha = max(alpha, value);
	}

	return value;
}

float HardComputer::evaluate() const
{
	// Should we add points if it can score a six
	const auto whiteCount = static_cast<float>(board_->sumCellsWithColor(white));
	const auto blackCount = static_cast<float>(board_->sumCellsWithColor(black));

	if (color_ == white)
	{
		return whiteCount - blackCount;
	}

	return blackCount - whiteCount;
}
