#include "BoardModel.h"


BoardModel::BoardModel()
{
	rowCount = 0;
	colCount = 0;
}

BoardModel::BoardModel(int rowCount, int colCount)
{
	this->rowCount = rowCount;
	this->colCount = colCount;

	grid.resize(rowCount);
	for (int i = 0; i < rowCount; i++)
	{
		grid[i].resize(colCount, Cell());
	}

	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			Position key = Position(i, j);
			Neighbours value = getNeighbors(key);
			positionToNeighboursMap[key] = value;
		}
	}

	const Capture directions = {
		Direction::up,
		Direction::right,
		Direction::down,
		Direction::left
	};

	captureCombintions = getCombinationsOfSizeKToN(directions, 2, 4);
}

BoardModel::~BoardModel()
{
}

Cell BoardModel::getCell(const Position position)
{
	assert(isWithinBounds(position));
	return grid[position.row][position.col];
}

Cell* BoardModel::getCellPointer(const Position position)
{
	if (isWithinBounds(position))
	{
		return &grid[position.row][position.col];
	}

	return nullptr;
}

int BoardModel::getColCount()
{
	return colCount;
}

int BoardModel::getRowCount()
{
	return rowCount;
}

BoardModel::Grid* BoardModel::getGrid()
{
	return &grid;
}

bool BoardModel::isWithinBounds(const Position position) const
{
	return (position.row >= 0 && position.row < rowCount
		&& position.col >= 0 && position.col < colCount);
}

BoardModel::Neighbours BoardModel::getNeighbors(const Position origin)
{
	Neighbours neighbors;

	neighbors[Direction::up] = getCellPointer(Position(origin.row - 1, origin.col));
	neighbors[Direction::right] = getCellPointer(Position(origin.row, origin.col + 1));
	neighbors[Direction::down] = getCellPointer(Position(origin.row + 1, origin.col));
	neighbors[Direction::left] = getCellPointer(Position(origin.row, origin.col - 1));

	return neighbors;
}

string BoardModel::getNeighboursInfo(Position position)
{
	Neighbours neighbours = positionToNeighboursMap[position];

	int pipSum = 0;
	string info = "";
	info.append("\nAdjacent info for last move at " +
		to_string(position.row + 1) + "," + to_string(position.col + 1) + ":\n\n");

	for (int i = 0; i < (int)Direction::size; ++i)
	{
		Cell* neighbour = neighbours[(Direction)i];

		if (neighbour == nullptr)
		{
			continue;
		}

		int pip = neighbour->getPip();
		pipSum += pip;

		if (neighbour->getColor() == black)
		{
			pip *= -1;
		}

		if (pip == 0)
		{
			continue;
		}

		info.append(directionEnumToString((Direction)i) + ": ");
		info.append(to_string(pip) + "\n");
	}
	info.append("Total pip counts: " + to_string(pipSum) + "\n");

	return info;
}

bool BoardModel::setMove(Move move)
{
	int pipSum = 0;

	if (!isMoveValid(move, pipSum))
	{
		return false;
	}

	history.push_back(grid);
	previousNeighbourInfo = getNeighboursInfo(move.position);

	Neighbours neighbours = positionToNeighboursMap[move.position];

	for (int i = 0; i < move.captureDirections.size(); ++i)
	{
		neighbours[move.captureDirections[i]]->capture();
	}

	Cell& cell = grid[move.position.row][move.position.col];
	cell.setColor(move.color);
	cell.setPip(pipSum);

	return true;
}

void BoardModel::undoMove()
{
	grid = history[history.size() - 1];
	history.pop_back();
}


bool BoardModel::isMoveValid(Move move, int& pipSum)
{
	// _ true
	if (mustCapture(move) && move.captureDirections.size() < MIN_CAPTURE_PIP)
	{
		return false;
	}

	return isWithinBounds(move.position)
		&& isCaptureValid(move, pipSum)
		&& isCellVacant(move.position);
}

bool BoardModel::isMoveValid(Move move)
{
	int temp;
	return isMoveValid(move, temp);
}

bool BoardModel::isCaptureValid(Move move, int & pipSum)
{
	if (move.captureDirections.size() == 0)
	{
		pipSum = 1;
		return true;
	}

	if (move.captureDirections.size() > (int)Direction::size
		|| move.captureDirections.size() == 1)
	{
		return false;
	}

	pipSum = 0;
	Neighbours neighbours = positionToNeighboursMap[move.position];

	for (int i = 0; i < move.captureDirections.size(); ++i) {

		Cell* neighbour = neighbours[move.captureDirections[i]];

		if (neighbour == nullptr
			|| neighbour->getColor() == noColor)
		{
			return false;
		}
	}

	for (int i = 0; i < move.captureDirections.size(); ++i)
	{
		Cell* neighbour = neighbours[move.captureDirections[i]];
		pipSum += neighbour->getPip();
	}

	if (pipSum > MAX_PIP)
	{
		pipSum = 1;
		return false;
	}

	return true;
}

bool BoardModel::mustCapture(Move move)
{
	Neighbours neighbours = positionToNeighboursMap[move.position];

	int occupiedCellCount = 0;
	int pipSum = 0;
	bool mustCapture = false;

	for (int i = 0; i < captureCombintions.size(); ++i)
	{
		Capture temp = captureCombintions[i];

		for (int j = 0; j < temp.size(); ++j)
		{
			if (neighbours[temp[j]] == nullptr)
			{
				continue;
			}
			if (neighbours[temp[j]]->getColor() != noColor)
			{
				++occupiedCellCount;
				pipSum += neighbours[temp[j]]->getPip();
			}
		}

		if (pipSum >= MIN_CAPTURE_PIP
			&& pipSum <= MAX_PIP
			&& occupiedCellCount >= 2)
		{
			mustCapture = true;
		}

		pipSum = 0;
		occupiedCellCount = 0;
	}

	return mustCapture;
}

bool BoardModel::isCellVacant(Position position)
{
	return grid[position.row][position.col].getColor() == noColor;
}

bool BoardModel::isBoardFull()
{
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			if (grid[i][j].getColor() == noColor)
			{
				return false;
			}
		}
	}

	return true;
}

Color BoardModel::getMajorityColor()
{
	int whiteCount = getTotalColorCount(white);
	int blackCount = getTotalColorCount(black);

	if (whiteCount > blackCount)
	{
		return white;
	}
	else if (whiteCount < blackCount)
	{
		return black;
	}

	return noColor;
}

int BoardModel::getTotalColorCount(Color color)
{
	int blackCount = 0;

	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			if (grid[i][j].getColor() == color)
			{
				++blackCount;
			}
		}
	}
	return blackCount;
}


vector<Move> BoardModel::getPossibleMoves(Color playerColor, Position position)
{
	vector<Move> potentialMoves;
	Move move = { position, playerColor, Capture() };

	if (!isCellVacant(move.position))
	{
		return potentialMoves;
	}

	if (isMoveValid(move))
	{
		potentialMoves.push_back(move);
	}

	if (getNeighbors(move.position).size() < MIN_CAPTURE_SIZE) {
		return potentialMoves;
	}

	for (int i = 0; i < captureCombintions.size(); ++i)
	{
		move.captureDirections = captureCombintions[i];

		if (isMoveValid(move))
		{
			potentialMoves.push_back(move);
		}
	}

	return potentialMoves;
}

vector<Move> BoardModel::getAllPossibleMoves(Color playerColor)
{
	vector<Move> potentialMoves;

	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			vector<Move> temp = getPossibleMoves(playerColor, Position(i, j));
			potentialMoves.insert(potentialMoves.end(), temp.begin(), temp.end());
		}
	}

	return potentialMoves;
}

Color BoardModel::findOpposition(Color playerColor)
{
	if (playerColor == white)
	{
		return black;
	}
	return white;
}
