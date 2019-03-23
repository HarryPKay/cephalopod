#include "Board.h"


Board::Board(int rowCount, int colCount)
{
	assert(colCount >= M_MIN && rowCount <= N_MAX);
	this->rowCount = rowCount;
	this->colCount = colCount;

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

Board::~Board()
{
}

Cell Board::getCell(const Position position)
{
	assert(isWithinBounds(position));
	return matrix[position.row][position.col];
}

Cell* Board::getCellPointer(const Position position)
{
	if (isWithinBounds(position)) {
		return &matrix[position.row][position.col];
	}

	return nullptr;
}

int Board::getColCount()
{
	return colCount;
}

int Board::getRowCount()
{
	return rowCount;
}

Matrix<Cell>* Board::getMatrix()
{
	return &matrix;
}

bool Board::isWithinBounds(const Position position) const
{
	return (position.row >= 0 && position.row < rowCount
		&& position.col >= 0 && position.col < colCount);
}

map<Direction, Cell*> Board::getAdjacenctCells(const Position origin)
{
	map<Direction, Cell*> adjacentCells;
	adjacentCells[Direction::up] = getCellPointer(Position(origin.row - 1, origin.col));
	adjacentCells[Direction::right] = getCellPointer(Position(origin.row, origin.col + 1));
	adjacentCells[Direction::down] = getCellPointer(Position(origin.row + 1, origin.col));
	adjacentCells[Direction::left] = getCellPointer(Position(origin.row, origin.col -1));

	return adjacentCells;
}

void Board::refreshPage() const
{
	for (int i = 0; i < REFRESH_PAGE_SIZE; ++i)
	{
		cout << endl;
	}
}

void Board::print()
{
	refreshPage();
	printColumnNumbers();
	printRowSeparator();
	printRows();
	cout << previousAdjacentInfo << endl;
}

void Board::printColumnNumbers()
{
	std::cout << "    ";
	for (int i = 0; i < colCount; ++i)
	{
		std::cout << (i + 1) << "   ";
	}
}

void Board::printRows()
{
	for (int i = 0; i < rowCount; ++i)
	{
		std::cout << (i + 1) << " |";
		for (int j = 0; j < colCount; ++j)
		{
			Color color = matrix[i][j].getColor();
			int pip = matrix[i][j].getPip();

			if (color == noColor)
			{
				std::cout << "   |";
			}
			else if (color == white)
			{
				std::cout << " " << pip << " |";
			}
			else if (color == black)
			{
				std::cout << "-" << pip << " |";
			}
			else
			{
				std::cout << " ?" << " |";
			}
		}

		printRowSeparator();
	}
}

void Board::printRowSeparator()
{
	std::cout << std::endl << "  ";
	for (int i = 0; i < colCount; ++i)
	{
		std::cout << " ---";
	}
	std::cout << std::endl;
}

string Board::getAdjacentInfo(Position position)
{
	map<Direction, Cell*> adjacentCells = matrix[position.row][position.col].getAdjacentCells();

	int pipSum = 0;
	string info = "";
	info.append("\nAdjacent info for last move at " +
		to_string(position.row) + "," + to_string(position.col) + ":\n\n");

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

// do we need a is valid move?
bool Board::setMove(Move move)
{
	Cell& cell = matrix[move.position.row][move.position.col];

	if (!isWithinBounds(move.position)
		|| cell.getColor() != noColor
		|| move.captureTargets.size() > 4
		|| move.captureTargets.size() == 1)
	{
		return false;
	}

	int pipSum = 0;
	map<Direction, Cell*> adjacentCells = cell.getAdjacentCells();
	for (int i = 0; i < move.captureTargets.size(); ++i)
	{
		Cell* adjacentCell = adjacentCells[move.captureTargets[i]];
		if (adjacentCell->getColor() != move.color)
		{
			pipSum += adjacentCell->getPip();
		}
	}

	if (pipSum == 0)
	{
		pipSum = 1;
	}

	if (pipSum > MAX_PIP)
	{
		return false;
	}

	bool isAllOpponentsCells = true;

	for (int i = 0; i < move.captureTargets.size(); ++i) {
		if (adjacentCells[move.captureTargets[i]]->getColor() == move.color)
		{
			isAllOpponentsCells = false;
		}
	}

	if (!isAllOpponentsCells)
	{
		return false;
	}

	previousAdjacentInfo = getAdjacentInfo(move.position);

	for (int i = 0; i < move.captureTargets.size(); ++i) {
		adjacentCells[move.captureTargets[i]]->capture();
	}

	cell.setColor(move.color);
	cell.setPip(pipSum);

	return true;
}

bool Board::isBoardFull()
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

Color Board::getMajorityColor()
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
