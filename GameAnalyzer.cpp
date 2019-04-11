#include "GameAnalyzer.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include "Helpers.h"

GameAnalyzer::GameAnalyzer(BoardModel* board)
{
	assert(board != nullptr);
	board_ = board;

	const Captures directions = {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	captureCombinations_ = getCombinationsOfSizeKtoN(directions, MIN_CAPTURE_SIZE, MAX_CAPTURE_SIZE);
}

PlayerColor GameAnalyzer::findMajorityColor() const
{
	const auto whiteCount = sumCellsWithColor(WHITE);
	const auto blackCount = sumCellsWithColor(BLACK);

	if (whiteCount > blackCount)
	{
		return WHITE;
	}
	if (whiteCount < blackCount)
	{
		return BLACK;
	}

	return NO_COLOR;
}

uint32_t GameAnalyzer::sumCellsWithColor(const PlayerColor color) const
{
	uint32_t colorCount = 0;

	for (uint32_t i = 0; i < board_->getRowCount(); ++i)
	{
		for (uint32_t j = 0; j < board_->getColCount(); ++j)
		{
			if (board_->getCell(Position(i, j)).getOccupantColor() == color)
			{
				++colorCount;
			}
		}
	}

	return colorCount;
}

uint32_t GameAnalyzer::sumPipForMove(Move move) const
{
	int32_t pipSum = 0;
	auto neighbors = board_->getNeighbors(move.position);

	for (auto captureDirection : move.captureDirections)
	{
		const auto neighbor = neighbors[captureDirection];
		pipSum += neighbor->getPip();
	}

	if (pipSum == 0)
	{
		pipSum = 1;
	}

	return pipSum;
}

vector<Move> GameAnalyzer::findPossibleMoves(const PlayerColor playerColor, const Position position)
{
	vector<Move> potentialMoves;
	Move move = {position, playerColor, Captures()};

	// Nothing to do.
	if (!board_->isCellVacant(move.position))
	{
		return potentialMoves;
	}

	if (isMoveValid(move))
	{
		potentialMoves.push_back(move);
	}

	for (const auto& captureCombination : captureCombinations_)
	{
		move.captureDirections = captureCombination;

		if (isMoveValid(move))
		{
			potentialMoves.push_back(move);
		}
	}

	return potentialMoves;
}

vector<Move> GameAnalyzer::findAllPossibleMoves(const PlayerColor playerColor)
{
	vector<Move> potentialMoves;

	for (uint32_t i = 0; i < board_->getRowCount(); ++i)
	{
		for (uint32_t j = 0; j < board_->getColCount(); ++j)
		{
			auto temp = findPossibleMoves(playerColor, Position(i, j));
			potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
		}
	}

	return potentialMoves;
}

void GameAnalyzer::printPossibleCaptures(const vector<Move>& moves) const
{
	// Nothing to do as there is only one selection.
	if (moves.size() == 1)
	{
		return;
	}

	auto neighbors = board_->getNeighbors(moves[0].position);

	for (uint32_t i = 0; i < moves.size(); ++i)
	{
		cout << std::setw(2) << i + 1 << ") Neighbors: ";

		auto move = moves[i];

		auto pipSum = 0;
		for (auto captureDirection : move.captureDirections)
		{
			const auto neighbor = neighbors[captureDirection];

			cout << directionEnumToString(captureDirection) << "("
				<< neighbor->getPip() << "), ";
			pipSum += neighbor->getPip();
		}

		cout << "Pip Sum = " << pipSum << "\n";
	}
	cout << "\n> ";
}

bool GameAnalyzer::isMoveValid(Move move)
{
	if (mustCapture(move) && move.captureDirections.size() < MIN_CAPTURE_PIP)
	{
		return false;
	}

	return board_->isWithinBounds(move.position)
		&& board_->isCellVacant(move.position)
		&& isCaptureValid(move);
}

bool GameAnalyzer::isCaptureValid(Move move)
{
	// Nothing to validate if there is no capture.
	if (move.captureDirections.empty())
	{
		return true;
	}

	// Capture direction_size is within the valid range of 2 and max.
	if (move.captureDirections.size() > static_cast<int>(DIRECTION_SIZE)
		|| move.captureDirections.size() == 1)
	{
		return false;
	}

	auto neighbors = board_->getNeighbors(move.position);

	// There is actually something to capture.
	for (auto captureDirection : move.captureDirections)
	{
		const auto neighbor = neighbors[captureDirection];

		if (neighbor == nullptr
			|| neighbor->getOccupantColor() == NO_COLOR)
		{
			return false;
		}
	}

	// Capture's pip sum does not exceed maximum.
	const auto pipSum = sumPipForMove(move);
	return pipSum <= MAX_PIP;
}

bool GameAnalyzer::mustCapture(const Move move)
{
	auto neighbors = board_->getNeighbors(move.position);

	auto mustCapture = false;

	for (const auto& temp : captureCombinations_)
	{
		uint32_t occupiedCellCount = 0;
		uint32_t pipSum = 0;

		for (auto j : temp)
		{
			if (neighbors[j] == nullptr)
			{
				continue;
			}
			if (neighbors[j]->getOccupantColor() != NO_COLOR)
			{
				++occupiedCellCount;
				pipSum += neighbors[j]->getPip();
			}
		}

		if (pipSum >= MIN_CAPTURE_PIP
			&& pipSum <= MAX_PIP
			&& occupiedCellCount >= 2)
		{
			mustCapture = true;
		}
	}

	return mustCapture;
}