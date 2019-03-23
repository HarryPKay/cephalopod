#include "Board.h"


Board::Board(int rowCount, int colCount)
{
	assert(colCount >= M_MIN && rowCount <= N_MAX);
	this->rowCount = rowCount;
	this->colCount = colCount;

	matrix.resize(rowCount);
	for (int i = 0; i < rowCount; i++)
	{
		matrix[i].resize(colCount, Die());
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
	matrix[3][3] = Die(getAdjacencyMap(Position(3, 3)));
	matrix[3][3].setPip(2);
	matrix[2][2] = Die(getAdjacencyMap(Position(2, 2)));
	matrix[2][2].setPip(2);
	matrix[4][4] = Die(getAdjacencyMap(Position(4, 4)));
	matrix[4][4].setPip(2);
	matrix[4][4].print();
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
	for (int i = 0; i < colCount; ++i)
	{
		std::cout << (i + 1) << " | ";
		for (int j = 0; j < rowCount; ++j)
		{
			if (matrix[j][i].getPip() == 0)
			{
				//std::cout << j << " a " << i << "\n";
				std::cout << " " << " | ";
			}
			else
			{
				std::cout << "?" << " | ";
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

Die * Board::getDiePtr(const Position position)
{
	if (position.row >= 0 && position.row < rowCount
		&& position.col >= 0 && position.col < colCount)
	{
		// TODO: check correct orientation.
		return &matrix[position.row][position.col];
	}

	return nullptr;
}

AdjacencyMap<Die*> Board::getAdjacencyMap(const Position origin)
{
	// TODO: size
	AdjacencyMap<Die*> adjacencyMap;

	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			adjacencyMap[i + 1][j + 1] = getDiePtr(Position(origin.row + i, origin.col + j));
		}
	}

	return adjacencyMap;
}
