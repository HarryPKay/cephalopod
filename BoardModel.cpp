#include "BoardModel.h"
#include "Helpers.h"
#include <cassert>

BoardModel::BoardModel(const uint32_t rowCount, const uint32_t colCount)
{
	this->rowCount_ = rowCount;
	this->colCount_ = colCount;

	grid_.resize(rowCount);
	for (uint32_t i = 0; i < rowCount; i++)
	{
		grid_[i].resize(colCount, Cell());
	}

	initializePositionToNeighborMapping();
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

uint32_t BoardModel::getColCount() const
{
	return colCount_;
}

uint32_t BoardModel::getRowCount() const
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

	neighbors[UP] = getCellPointer(Position(origin.row - 1, origin.col));
	neighbors[RIGHT] = getCellPointer(Position(origin.row, origin.col + 1));
	neighbors[DOWN] = getCellPointer(Position(origin.row + 1, origin.col));
	neighbors[LEFT] = getCellPointer(Position(origin.row, origin.col - 1));

	return neighbors;
}

string BoardModel::getNeighborsInfo() const
{
	return neighborInfo_;
}

void BoardModel::setNeighborsInfo(const Position position)
{
	auto neighbors = positionToNeighborsMap_[position];

	int32_t pipSum = 0;
	string info;
	info.append(
		"\nPrevious neighbor information for position: " +
		to_string(position.row + 1) +
		"," + to_string(position.col + 1) +
		":\n\n");

	for (auto i = 0; i < DIRECTION_SIZE; ++i)
	{
		const auto neighbor = neighbors[static_cast<Direction>(i)];

		if (neighbor == nullptr)
		{
			continue;
		}

		auto pip = neighbor->getPip();
		pipSum += pip;

		if (neighbor->getOccupantColor() == BLACK)
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
	if (pipSum == 0)
	{
		info = "\nNo neighbors occupied for position: " + to_string(position.row + 1) + "," +
			to_string(position.col + 1) + ":\n\n";
	}

	neighborInfo_ = info;
}

bool BoardModel::setMove(Move move, const int32_t pip)
{
	assert(pip >= MIN_PIP && pip <= MAX_PIP);

	if (!isCellVacant(move.position) && !isWithinBounds(move.position))
	{
		return false;
	}

	gridHistory_.push(grid_);
	setNeighborsInfo(move.position);

	auto neighbors = positionToNeighborsMap_[move.position];

	auto& cell = grid_[move.position.row][move.position.col];
	cell.setOccupantColor(move.color);
	cell.setPip(pip);

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
	for (uint32_t i = 0; i < rowCount_; ++i)
	{
		for (uint32_t j = 0; j < colCount_; ++j)
		{
			auto position = Position(i, j);
			const auto neighbor = getNeighbors(position);
			positionToNeighborsMap_[position] = neighbor;
		}
	}
}

bool BoardModel::isCellVacant(const Position position)
{
	if (!isWithinBounds(position))
	{
		return false;
	}

	return grid_[position.row][position.col].getOccupantColor() == NO_COLOR;
}

bool BoardModel::isBoardFull()
{
	for (uint32_t i = 0; i < rowCount_; ++i)
	{
		for (uint32_t j = 0; j < colCount_; ++j)
		{
			if (grid_[i][j].getOccupantColor() == NO_COLOR)
			{
				return false;
			}
		}
	}

	return true;
}
