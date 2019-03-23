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

void Board::print()
{
	// Print header
	printColumnNumbers();
	printRowSeparator();
	printRows();
}

void Board::test()
{
	matrix[3][3].setColor(black);
	matrix[3][3].setPip(1);
	matrix[3][3].printAdjacentInfo();
	matrix[2][3].setColor(white);
	matrix[2][3].setPip(1);
	matrix[4][3].setColor(white);
	matrix[4][3].setPip(1);
	matrix[3][4].setColor(white);
	matrix[3][4].setPip(1);
	matrix[3][2].setColor(white);
	matrix[3][2].setPip(1);
	matrix[3][3].printAdjacentInfo();
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
			if (matrix[i][j].getColor() == noColor)
			{
				std::cout << "   |";
			}
			else if (matrix[i][j].getColor() == white)
			{
				std::cout << " " << matrix[i][j].getPip() << " |";
			}
			else if (matrix[i][j].getColor() == black)
			{
				std::cout << "-" << matrix[i][j].getPip() << " |";
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