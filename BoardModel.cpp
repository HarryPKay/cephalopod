#include "BoardModel.h"


BoardModel::BoardModel()
{
	rowCount = 0;
	colCount = 0;
}


BoardModel::BoardModel(int rowCount, int colCount, vector<vector<Direction>> potentialCaptures)
{
	assert(colCount >= M_MIN && rowCount <= N_MAX);
	this->rowCount = rowCount;
	this->colCount = colCount;
	this->potentialCaptures = potentialCaptures;

	matrix.resize(rowCount);
	for (int i = 0; i < rowCount; i++)
	{
		matrix[i].resize(colCount, Cell());
	}

	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			matrix[i][j].setAdjacentCells(getAdjacenctCells(Position(i, j)));
		}
	}
}

BoardModel::~BoardModel()
{
}

Cell BoardModel::getCell(const Position position)
{
	assert(isWithinBounds(position));
	return matrix[position.row][position.col];
}

Cell* BoardModel::getCellPointer(const Position position)
{
	if (isWithinBounds(position)) {
		return &matrix[position.row][position.col];
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

Matrix<Cell>* BoardModel::getMatrix()
{
	return &matrix;
}

bool BoardModel::isWithinBounds(const Position position) const
{
	return (position.row >= 0 && position.row < rowCount
		&& position.col >= 0 && position.col < colCount);
}

map<Direction, Cell*> BoardModel::getAdjacenctCells(const Position origin)
{
	map<Direction, Cell*> adjacentCells;
	adjacentCells[Direction::up] = getCellPointer(Position(origin.row - 1, origin.col));
	adjacentCells[Direction::right] = getCellPointer(Position(origin.row, origin.col + 1));
	adjacentCells[Direction::down] = getCellPointer(Position(origin.row + 1, origin.col));
	adjacentCells[Direction::left] = getCellPointer(Position(origin.row, origin.col -1));

	return adjacentCells;
}

string BoardModel::getAdjacentInfo(Position position)
{
	map<Direction, Cell*> adjacentCells = matrix[position.row][position.col].getAdjacentCells();

	int pipSum = 0;
	string info = "";
	info.append("\nAdjacent info for last move at " +
		to_string(position.row + 1) + "," + to_string(position.col + 1) + ":\n\n");

	for (int i = 0; i < (int)Direction::size; ++i)
	{
		Cell* cell = adjacentCells[(Direction)i];

		if (cell == nullptr)
		{
			continue;
		}

		int pip = cell->getPip();
		pipSum += pip;

		if (cell->getColor() == black)
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

	previousAdjacentInfo = getAdjacentInfo(move.position);

	Cell& cell = matrix[move.position.row][move.position.col];
	map<Direction, Cell*> adjacentCells = cell.getAdjacentCells();


	for (int i = 0; i < move.captureTargets.size(); ++i)
	{
		adjacentCells[move.captureTargets[i]]->capture();
	}

	cell.setColor(move.color);
	cell.setPip(pipSum);

	return true;
}


bool BoardModel::isMoveValid(Move move, int& pipSum)
{
	// _ true
	if (mustCapture(move) && move.captureTargets.size() < 2) 
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
	if (move.captureTargets.size() == 0)
	{
		pipSum = 1;
		return true;
	}

	if (move.captureTargets.size() > 4
		|| move.captureTargets.size() == 1)
	{
		return false;
	}

	pipSum = 0;
	Cell& cell = matrix[move.position.row][move.position.col];
	map<Direction, Cell*> adjacentCells = cell.getAdjacentCells();

	for (int i = 0; i < move.captureTargets.size(); ++i) {

		Cell* adjacentCell = adjacentCells[move.captureTargets[i]];

		if (adjacentCell == nullptr
			|| adjacentCell->getColor() == noColor)
		{
			return false;
		}
	}

	for (int i = 0; i < move.captureTargets.size(); ++i)
	{
		Cell* adjacentCell = adjacentCells[move.captureTargets[i]];
		pipSum += adjacentCell->getPip();
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
	Cell& cell = matrix[move.position.row][move.position.col];
	map<Direction, Cell*> adjacentCells = cell.getAdjacentCells();

	int occupiedCellCount = 0;
	int pipSum = 0;
	bool mustCapture = false;

	for (int i = 0; i < potentialCaptures.size(); ++i)
	{
		vector<Direction> temp = potentialCaptures[i];

		for (int j = 0; j < temp.size(); ++j)
		{
			if (adjacentCells[temp[j]] == nullptr)
			{
				continue;
			}
			if (adjacentCells[temp[j]]->getColor() != noColor) 
			{
				++occupiedCellCount;
				pipSum += adjacentCells[temp[j]]->getPip();
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
	return matrix[position.row][position.col].getColor() == noColor;
}

bool BoardModel::isBoardFull()
{
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			if (matrix[i][j].getColor() == noColor)
			{
				return false;
			}
		}
	}

	return true;
}

Color BoardModel::getMajorityColor()
{
	int whiteCount = 0;
	int blackCount = 0;

	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			if (matrix[i][j].getColor() == black)
			{
				++blackCount;
			}
			if (matrix[i][j].getColor() == white)
			{
				++whiteCount;
			}
		}
	}

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
