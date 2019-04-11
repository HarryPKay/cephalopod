#include "HardComputer.h"
#include "Helpers.h"

HardComputer::HardComputer(
	const PlayerColor playerColor,
	GameAnalyzer* gameAnalyzer,
	BoardModel* boardModel,
	const AiAlgorithm algorithmType,
	const uint32_t depth)
	: Player(playerColor, gameAnalyzer)
	  , board_(boardModel)
	  , algorithmType_(algorithmType)
	  , depth_(depth)
{
}

Move HardComputer::promptForMove()
{
	switch (algorithmType_)
	{
	case MINIMAX: return minimax();
	default: return alphaBeta();
	}
}

Move HardComputer::minimax()
{
	map<float_t, Move> valueMoveMap;
	auto moves = gameAnalyzer_->findAllPossibleMoves(playerColor_);

	for (const auto& move : moves)
	{
		const auto pipSum = gameAnalyzer_->sumPipForMove(move);
		board_->setMove(move, pipSum);

		auto value = minValue(depth_ - 1);
		valueMoveMap[value] = move;
		board_->undoMove();
	}

	// Retrieve the largest key
	const auto key = valueMoveMap.rbegin()->first;
	return valueMoveMap[key];
}

Move HardComputer::alphaBeta()
{
	map<float_t, Move> valueMoveMap;
	auto moves = gameAnalyzer_->findAllPossibleMoves(playerColor_);

	for (const auto& move : moves)
	{
		const auto pipSum = gameAnalyzer_->sumPipForMove(move);
		board_->setMove(move, pipSum);
		auto value = minValue(depth_ - 1, -INFINITY, INFINITY);
		valueMoveMap[value] = move;
		board_->undoMove();
	}

	const auto key = valueMoveMap.rbegin()->first;
	return valueMoveMap[key];
}

float_t HardComputer::minValue(const uint32_t depth)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate();
	}

	// general case: there are board states to search.
	auto value = INFINITY;
	auto moves = gameAnalyzer_->findAllPossibleMoves(oppositionColor_);

	for (const auto& move : moves)
	{
		const auto pipSum = gameAnalyzer_->sumPipForMove(move);
		board_->setMove(move, pipSum);
		value = min(value, maxValue(depth - 1));
		board_->undoMove();
	}

	return value;
}

float_t HardComputer::minValue(const uint32_t depth, const float_t alpha, float_t beta)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate();
	}

	// general case: there are board states to search.
	auto value = INFINITY;
	auto moves = gameAnalyzer_->findAllPossibleMoves(oppositionColor_);

	for (const auto& move : moves)
	{
		const auto pipSum = gameAnalyzer_->sumPipForMove(move);
		board_->setMove(move, pipSum);
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

float_t HardComputer::maxValue(const uint32_t depth)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate();
	}

	// general case: there are board states to search.
	auto value = -INFINITY;
	auto moves = gameAnalyzer_->findAllPossibleMoves(playerColor_); // This computer's color

	for (const auto& move : moves)
	{
		const auto pipSum = gameAnalyzer_->sumPipForMove(move);
		board_->setMove(move, pipSum);
		value = max(value, minValue(depth - 1));
		board_->undoMove();
	}

	return value;
}

float_t HardComputer::maxValue(const uint32_t depth, float_t alpha, const float_t beta)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate();
	}

	// general case: there are board states to search.
	auto value = -INFINITY;
	auto moves = gameAnalyzer_->findAllPossibleMoves(playerColor_); // This computer's color

	for (const auto& move : moves)
	{
		const auto pipSum = gameAnalyzer_->sumPipForMove(move);
		board_->setMove(move, pipSum);
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

float_t HardComputer::evaluate() const
{
	const auto whiteCount = static_cast<float_t>(gameAnalyzer_->sumCellsWithColor(WHITE));
	const auto blackCount = static_cast<float_t>(gameAnalyzer_->sumCellsWithColor(BLACK));

	if (playerColor_ == WHITE)
	{
		return whiteCount - blackCount;
	}

	return blackCount - whiteCount;
}
