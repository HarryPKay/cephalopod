#include "HardComputer.h"
#include "Helpers.h"

HardComputer::HardComputer(
	const PlayerColor playerColor,
	GameAnalyzer* gameAnalyzer,
	BoardModel* boardModel,
	const AiAlgorithm algorithmType,
	const uint32_t depth
)
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
	case ALPHABETA: return alphaBeta();
	default: return monteCarlo();
	}
}

Move HardComputer::minimax()
{
	map<float_t, Move> valueMoveMap;
	auto moves = gameAnalyzer_->findAllValidMoves(playerColor_);

	// For each move, record its evaluation.
	for (const auto& move : moves)
	{
		board_->setMove(move);
		auto value = minValue(depth_ - 1);
		valueMoveMap[value] = move;
		board_->undoMove();
	}

	// Return the move that had the highest evaluation.
	return valueMoveMap.rbegin()->second;
}

Move HardComputer::alphaBeta()
{
	map<float_t, Move> valueMoveMap;
	auto moves = gameAnalyzer_->findAllValidMoves(playerColor_);

	// For each move, record its evaluation.
	for (const auto& move : moves)
	{
		board_->setMove(move);
		auto value = minValue(depth_ - 1, -INFINITY, INFINITY);
		valueMoveMap[value] = move;
		board_->undoMove();
	}

	// Return the move that had the highest evaluation.
	return valueMoveMap.rbegin()->second;
}

Move HardComputer::monteCarlo() const
{
	auto moves = gameAnalyzer_->findAllValidMoves(playerColor_);
	map<float_t, Move> valueMoveMapping;

	// For each move, record its evaluation.
	for (const auto& move : moves)
	{
		board_->setMove(move);
		// If this move ends with a win, nothing to do, so return early.
		if (gameAnalyzer_->findWinnersColor() == playerColor_)
		{
			board_->undoMove();
			return move;
		}
		auto value = simulation();
		valueMoveMapping[value] = move;
		board_->undoMove();
	}
	auto move = valueMoveMapping.rbegin()->second;

	// Ensure that the correct neighbor information is shown.
	board_->setNeighborsInfo(move.position);

	return move;
}

float_t HardComputer::simulation() const
{
	float_t value = 0;

	for (uint32_t i = 0; i < SIMULATION_COUNT; ++i)
	{
		value += expansion(0, oppositionColor_);
	}

	return value / SIMULATION_COUNT;
}

float_t HardComputer::expansion(const uint32_t moveCount, const PlayerColor color) const
{
	// Base case, the board has reached terminal state.
	if (board_->isBoardFull())
	{
		// Rewind all of the moves that have been set in this simulation before return.
		for (uint32_t i = 0; i < moveCount; ++i)
		{
			board_->undoMove();
		}
		return evaluate(GAME_RESULT_ENCODING);
	}

	// General case: the board is unfinished.
	auto moves = gameAnalyzer_->findAllValidMoves(color);
	const auto index = rand() % moves.size();
	const auto move = moves[index];
	board_->setMove(move);
	return expansion(moveCount + 1, findOpposition(color));
}

float_t HardComputer::minValue(const uint32_t depth)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate(OCCUPANT_COUNT_DIFFERENCE);
	}

	// General case: there are board states to search.
	auto value = INFINITY;
	auto moves = gameAnalyzer_->findAllValidMoves(oppositionColor_);
	for (const auto& move : moves)
	{
		board_->setMove(move);
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
		return evaluate(OCCUPANT_COUNT_DIFFERENCE);
	}

	// General case: there are board states to search.
	auto value = INFINITY;
	auto moves = gameAnalyzer_->findAllValidMoves(oppositionColor_);
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

float_t HardComputer::maxValue(const uint32_t depth)
{
	// Base case: board is full or depth of search reaches 0.
	if (depth == 0 || board_->isBoardFull())
	{
		return evaluate(OCCUPANT_COUNT_DIFFERENCE);
	}

	// General case: there are board states to search.
	auto value = -INFINITY;
	auto moves = gameAnalyzer_->findAllValidMoves(playerColor_);
	for (const auto& move : moves)
	{
		board_->setMove(move);
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
		return evaluate(OCCUPANT_COUNT_DIFFERENCE);
	}

	// General case: there are board states to search.
	auto value = -INFINITY;
	auto moves = gameAnalyzer_->findAllValidMoves(playerColor_);
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

float_t HardComputer::evaluate(const HeuristicMethod method) const
{
	const auto whiteCount = static_cast<float_t>(gameAnalyzer_->countCellsWithColor(WHITE));
	const auto blackCount = static_cast<float_t>(gameAnalyzer_->countCellsWithColor(BLACK));
	const auto winner = gameAnalyzer_->findWinnersColor();

	switch (method)
	{
	case OCCUPANT_COUNT_DIFFERENCE:

		// Counts the number of occupancies and returns a difference that is
		// maximized for the maxing player and minimized for the mining player.
		if (playerColor_ == WHITE)
		{
			return whiteCount - blackCount;
		}
		return blackCount - whiteCount;

	case GAME_RESULT_ENCODING:

		//Encodes the result of games with a 1 for a win or a 0 for a loss.
		if (winner == playerColor_)
		{
			return 1.0;
		}
		if (winner == oppositionColor_)
		{
			return 0.0;
		}
	}
	return 0.0;
}
