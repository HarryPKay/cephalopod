#include "GameAnalyzer.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include "Helpers.h"

GameAnalyzer::GameAnalyzer(BoardModel* board)
{
	assert(board != nullptr);
	board_ = board;

	// Ensure that each possible combination of captures is generated.
	const Captures directions = {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};
	captureCombinations_ = findCombinationsOfSizeKtoN(directions, MIN_CAPTURE_SIZE, MAX_CAPTURE_SIZE);
}

PlayerColor GameAnalyzer::findMajorityColor() const
{
	// Count how many cells are owned by each player and then
	// return the color of the player who owns the most.
	const auto whiteCount = countCellsWithColor(WHITE);
	const auto blackCount = countCellsWithColor(BLACK);
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

PlayerColor GameAnalyzer::findWinnersColor() const
{
	if (board_->isBoardFull())
	{
		return findMajorityColor();
	}

	return NO_COLOR;
}

uint32_t GameAnalyzer::countCellsWithColor(const PlayerColor color) const
{
	// For each cell on the board, count the color found on that cell.
	uint32_t colorCount = 0;
	for (uint32_t i = 0; i < board_->getRowCount(); ++i)
	{
		for (uint32_t j = 0; j < board_->getColCount(); ++j)
		{
			if (board_->getCell(Position(i, j)).occupant == color)
			{
				++colorCount;
			}
		}
	}
	return colorCount;
}

void GameAnalyzer::displayWinner() const
{
	// The winner is the player who occupies the most cells.
	assert(board_->isBoardFull());
	const auto color = findMajorityColor();
	if (color == BLACK)
	{
		cout << "\nBLACK WINS\n";
	}
	else if (color == WHITE)
	{
		cout << "\nWHITE WINS\n";
	}
	else
	{
		cout << "\nDRAW\n";
	}
}

uint32_t GameAnalyzer::sumPipForMove(Move move) const
{
	// For each neighbor, sum the pip.
	int32_t pipSum = 0;
	auto neighbors = board_->getNeighbors(move.position);
	for (auto captureDirection : move.captureDirections)
	{
		const auto neighbor = neighbors[captureDirection];
		pipSum += neighbor->pip;
	}

	// If it is found that the pipSum is zero, assume that
	// this move is a non-capture and return 1 instead.
	if (pipSum == 0)
	{
		pipSum = 1;
	}

	return pipSum;
}

vector<Move> GameAnalyzer::findValidMoves(const PlayerColor playerColor, const Position position)
{
	vector<Move> potentialMoves;
	Move move = {position, playerColor, Captures(), MIN_PIP};

	// Nothing to do, no possible moves for a occupied cell.
	if (!board_->isCellVacant(move.position))
	{
		return potentialMoves;
	}

	// Record the first move: the move where there are no captures.
	if (isMoveValid(move))
	{
		potentialMoves.push_back(move);
	}

	// Record all of the moves that involve a capture
	for (const auto& captureCombination : captureCombinations_)
	{
		move.captureDirections = captureCombination;
		if (isMoveValid(move))
		{
			move.pipSum = sumPipForMove(move);
			potentialMoves.push_back(move);
		}
	}

	return potentialMoves;
}

vector<Move> GameAnalyzer::findAllValidMoves(const PlayerColor playerColor)
{
	// For each position, find the available moves and append it to the total
	// available moves for all positions.
	vector<Move> potentialMoves;
	for (uint32_t i = 0; i < board_->getRowCount(); ++i)
	{
		for (uint32_t j = 0; j < board_->getColCount(); ++j)
		{
			auto temp = findValidMoves(playerColor, Position(i, j));
			potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
		}
	}

	return potentialMoves;
}

void GameAnalyzer::printValidCaptures(const vector<Move>& moves) const
{
	// Nothing to do as there is only one selection.
	if (moves.size() == 1)
	{
		return;
	}

	// For each possible capture, print out the neighbors to capture,
	// their pip and the direction that they exist, relative to the current
	// position.
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
				<< neighbor->pip << "), ";
			pipSum += neighbor->pip;
		}

		cout << "Pip Sum = " << pipSum << "\n";
	}
	cout << "\n> ";
}

bool GameAnalyzer::isMoveValid(Move move)
{
	// Check everything that could make this an invalid move.
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

	// Check Capture direction_size is within the valid range of 2 and max.
	if (move.captureDirections.size() > static_cast<int>(DIRECTION_SIZE)
		|| move.captureDirections.size() == 1)
	{
		return false;
	}

	// Else there is actually something to capture. Ensure that those captures
	// are capturing the opposition and not vacant cells.
	auto neighbors = board_->getNeighbors(move.position);
	for (auto captureDirection : move.captureDirections)
	{
		const auto neighbor = neighbors[captureDirection];

		if (neighbor == nullptr
			|| neighbor->occupant == NO_COLOR)
		{
			return false;
		}
	}

	// Check that the capture's pip sum does not exceed maximum.
	const auto pipSum = sumPipForMove(move);
	return pipSum <= MAX_PIP;
}

bool GameAnalyzer::mustCapture(const Move move)
{
	// For each capture relative to the position of the move.
	// Check to see that a capture is valid. If it is, then the move must
	// be a capture by the game rules.
	auto neighbors = board_->getNeighbors(move.position);
	auto mustCapture = false;
	for (const auto& temp : captureCombinations_)
	{
		uint32_t occupiedCellCount = 0;
		uint32_t pipSum = 0;

		// if the occupied cell count is greater than 2 and the pip sum is less or
		// equal than the max pip sum, then this move must be a capture.
		for (auto j : temp)
		{
			if (neighbors[j] == nullptr)
			{
				continue;
			}
			if (neighbors[j]->occupant != NO_COLOR)
			{
				++occupiedCellCount;
				pipSum += neighbors[j]->pip;
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
