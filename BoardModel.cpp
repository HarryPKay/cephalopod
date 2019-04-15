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

	// Ensure that a mapping exists from the start.
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


bool BoardModel::isWithinBounds(const Position position) const
{
	return (position.row >= 0 && position.row < rowCount_
		&& position.col >= 0 && position.col < colCount_);
}

BoardModel::Neighbors BoardModel::getNeighbors(const Position origin)
{
	return positionToNeighborsMap_[origin];
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

	// Gather information on previous move location.
	info.append(
		"\nPrevious neighbor information for position: " +
		to_string(position.row + 1) +
		"," + to_string(position.col + 1) +
		":\n\n");

	// For each possible direction a neighbor could exist in.
	for (auto i = 0; i < DIRECTION_SIZE; ++i)
	{
		const auto neighbor = neighbors[static_cast<Direction>(i)];

		// If there isn't a neighbor, then nothing to do.
		if (neighbor == nullptr)
		{
			continue;
		}

		// record the individual pip and the total pip.
		auto pip = neighbor->pip;
		pipSum += pip;

		if (neighbor->occupant == BLACK)
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

	// If there wasn't actually any neighbors occupied. Change the message
	// to reflect this.
	if (pipSum == 0)
	{
		info = "\nNo neighbors occupied for position: " + to_string(position.row + 1) + "," +
			to_string(position.col + 1) + ":\n\n";
	}

	neighborInfo_ = info;
}

bool BoardModel::setMove(Move move)
{
	// Will this move leave the board in a consistent state?
	if (!isCellVacant(move.position) && !isWithinBounds(move.position))
	{
		return false;
	}

	// Record the current state before altering.
	gridHistory_.push(grid_);
	setNeighborsInfo(move.position);

	// Update the targeted cell.
	auto neighbors = positionToNeighborsMap_[move.position];
	auto& cell = grid_[move.position.row][move.position.col];
	cell.occupant = move.color;
	cell.pip = move.pipSum;

	// Capture the desired cells.
	for (auto captureDirection : move.captureDirections)
	{
		auto neighbor = neighbors[captureDirection];
		neighbor->occupant = NO_COLOR;
		neighbor->pip = NO_DICE;
	}

	return true;
}

void BoardModel::undoMove()
{
	grid_ = gridHistory_.top();
	gridHistory_.pop();

	// Call this in the case that pointers need to be updated.
	initializePositionToNeighborMapping();
}

void BoardModel::initializePositionToNeighborMapping()
{
	for (uint32_t i = 0; i < rowCount_; ++i)
	{
		for (uint32_t j = 0; j < colCount_; ++j)
		{
			// For each possible direction a neighbor can exist in, create the 
			// corresponding mapping
			auto position = Position(i, j);
			Neighbors neighbors;
			neighbors[UP] = getCellPointer(Position(position.row - 1, position.col));
			neighbors[RIGHT] = getCellPointer(Position(position.row, position.col + 1));
			neighbors[DOWN] = getCellPointer(Position(position.row + 1, position.col));
			neighbors[LEFT] = getCellPointer(Position(position.row, position.col - 1));
			positionToNeighborsMap_[position] = neighbors;
		}
	}
}

bool BoardModel::isCellVacant(const Position position)
{
	if (!isWithinBounds(position))
	{
		return false;
	}

	return grid_[position.row][position.col].occupant == NO_COLOR;
}

bool BoardModel::isBoardFull()
{
	for (uint32_t i = 0; i < rowCount_; ++i)
	{
		for (uint32_t j = 0; j < colCount_; ++j)
		{
			if (grid_[i][j].occupant == NO_COLOR)
			{
				return false;
			}
		}
	}

	return true;
}
