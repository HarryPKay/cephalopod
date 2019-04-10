#include "BoardModel.h"
#include <cassert>
#include "Helpers.h"

BoardModel::BoardModel()
{
	rowCount_ = 0;
	colCount_ = 0;
}

BoardModel::BoardModel(const int rowCount, const int colCount)
{
	this->rowCount_ = rowCount;
	this->colCount_ = colCount;

	grid_.resize(rowCount);
	for (auto i = 0; i < rowCount; i++)
	{
		grid_[i].resize(colCount, Cell());
	}

	initializePositionToNeighborMapping();

	const Captures directions = {
		Direction::up,
		Direction::right,
		Direction::down,
		Direction::left
	};

	captureCombinations_ = getCombinationsOfSizeKToN(directions, 2, 4);
}

Cell BoardModel::getCell(const Position position)
{
	assert(isWithinBounds(position));
	return grid_[position.row][position.col];
}

Cell* BoardModel::getCellPointer(const Position position)
{
	if (isWithinBounds(position))
	{
		return &grid_[position.row][position.col];
	}

	return nullptr;
}

int BoardModel::getColCount() const
{
	return colCount_;
}

int BoardModel::getRowCount() const
{
	return rowCount_;
}

BoardModel::Grid* BoardModel::getGrid()
{
	return &grid_;
}

bool BoardModel::isWithinBounds(const Position position) const
{
	return (position.row >= 0 && position.row < rowCount_
		&& position.col >= 0 && position.col < colCount_);
}

BoardModel::Neighbors BoardModel::getNeighbors(const Position origin)
{
	Neighbors neighbors;

	neighbors[Direction::up] = getCellPointer(Position(origin.row - 1, origin.col));
	neighbors[Direction::right] = getCellPointer(Position(origin.row, origin.col + 1));
	neighbors[Direction::down] = getCellPointer(Position(origin.row + 1, origin.col));
	neighbors[Direction::left] = getCellPointer(Position(origin.row, origin.col - 1));

	return neighbors;
}

string BoardModel::getNeighborsInfo() const
{
	return neighborInfo_;
}

void BoardModel::setNeighborsInfo(const Position position)
{
	auto neighbors = positionToNeighborsMap_[position];

	auto pipSum = 0;
	string info;
	info.append("\nNeighbor information for position: " +
		to_string(position.row + 1) + "," + to_string(position.col + 1) + ":\n\n");

	for (auto i = 0; i < static_cast<int>(Direction::size); ++i)
	{
		auto neighbor = neighbors[static_cast<Direction>(i)];

		if (neighbor == nullptr)
		{
			continue;
		}

		auto pip = neighbor->getPip();
		pipSum += pip;

		if (neighbor->getColor() == black)
		{
			pip *= -1;
		}

		if (pip == 0)
		{
			continue;
		}

		info.append(directionEnumToString(static_cast<Direction>(i)) + ": ");
		info.append(to_string(pip) + "\n");
	}
	info.append("Total pip counts: " + to_string(pipSum) + "\n\n");

	// If there wasn't actually any neighbors occupied, nothing to print.
	if (pipSum == 0) {
		info = "\nNo neighbors occupied for position: " + to_string(position.row + 1) + "," + to_string(position.col + 1) + ":\n\n";
	}

	neighborInfo_ = info;
}

bool BoardModel::setMove(Move move)
{
	if (!isMoveValid(move))
	{
		return false;
	}

	gridHistory_.push(grid_);
	setNeighborsInfo(move.position);

	auto neighbors = positionToNeighborsMap_[move.position];

	auto& cell = grid_[move.position.row][move.position.col];
	cell.setOccupant(move.color);
	cell.setPip(sumPipForMove(move));

	for (auto captureDirection : move.captureDirections)
	{
		neighbors[captureDirection]->capture();
	}

	return true;
}

void BoardModel::undoMove()
{
	grid_ = gridHistory_.top();
	gridHistory_.pop();
	initializePositionToNeighborMapping();
}

void BoardModel::initializePositionToNeighborMapping()
{
	// possible issue with stack and pointers
	for (auto i = 0; i < rowCount_; ++i)
	{
		for (auto j = 0; j < colCount_; ++j)
		{
			auto position = Position(i, j);
			const auto neighbor = getNeighbors(position);
			positionToNeighborsMap_[position] = neighbor;
		}
	}
}


bool BoardModel::isMoveValid(Move move)
{
	if (mustCapture(move) && move.captureDirections.size() < MIN_CAPTURE_PIP)
	{
		return false;
	}

	return isCellVacant(move.position)
		&& isWithinBounds(move.position)
		&& isCaptureValid(move);
}

bool BoardModel::isCaptureValid(Move move)
{
	// Nothing to validate if there is no capture.
	if (move.captureDirections.empty())
	{
		return true;
	}

	// Capture size is within the valid range of 2 and max.
	if (move.captureDirections.size() > static_cast<int>(Direction::size)
		|| move.captureDirections.size() == 1)
	{
		return false;
	}

	auto neighbors = positionToNeighborsMap_[move.position];

	// There is actually something to capture.
	for (auto captureDirection : move.captureDirections)
	{
		auto neighbor = neighbors[captureDirection];

		if (neighbor == nullptr
			|| neighbor->getColor() == noColor)
		{
			return false;
		}
	}

	// Capture's pip sum does not exceed maximum.
	const auto pipSum = sumPipForMove(move);
	return pipSum <= MAX_PIP;
}

bool BoardModel::mustCapture(const Move move)
{
	auto neighbors = positionToNeighborsMap_[move.position];

	auto mustCapture = false;

	for (const auto& temp : captureCombinations_)
	{
		auto occupiedCellCount = 0;
		auto pipSum = 0;

		for (auto j : temp)
		{
			if (neighbors[j] == nullptr)
			{
				continue;
			}
			if (neighbors[j]->getColor() != noColor)
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

bool BoardModel::isCellVacant(const Position position)
{
	if (!isWithinBounds(position))
	{
		return false;
	}

	return grid_[position.row][position.col].getColor() == noColor;
}

bool BoardModel::isBoardFull()
{
	for (auto i = 0; i < rowCount_; ++i)
	{
		for (auto j = 0; j < colCount_; ++j)
		{
			if (grid_[i][j].getColor() == noColor)
			{
				return false;
			}
		}
	}

	return true;
}

Color BoardModel::findMajorityColor()
{
	const auto whiteCount = sumCellsWithColor(white);
	const auto blackCount = sumCellsWithColor(black);

	if (whiteCount > blackCount)
	{
		return white;
	}
	if (whiteCount < blackCount)
	{
		return black;
	}

	return noColor;
}

int BoardModel::sumCellsWithColor(const Color color)
{
	auto blackCount = 0;

	for (auto i = 0; i < rowCount_; ++i)
	{
		for (auto j = 0; j < colCount_; ++j)
		{
			if (grid_[i][j].getColor() == color)
			{
				++blackCount;
			}
		}
	}

	return blackCount;
}

int BoardModel::sumPipForMove(Move move)
{
	auto pipSum = 0;
	auto neighbors = getNeighbors(move.position);

	for (auto captureDirection : move.captureDirections)
	{
		auto neighbor = neighbors[captureDirection];
		pipSum += neighbor->getPip();
	}

	if (pipSum == 0)
	{
		pipSum = 1;
	}

	return pipSum;
}


vector<Move> BoardModel::findPossibleMoves(const Color playerColor, const Position position)
{
	vector<Move> potentialMoves;
	Move move = { position, playerColor, Captures() };

	// Nothing to do.
	if (!isCellVacant(move.position))
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

vector<Move> BoardModel::findAllPossibleMoves(const Color playerColor)
{
	vector<Move> potentialMoves;

	for (auto i = 0; i < rowCount_; ++i)
	{
		for (auto j = 0; j < colCount_; ++j)
		{
			auto temp = findPossibleMoves(playerColor, Position(i, j));
			potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
		}
	}

	return potentialMoves;
}