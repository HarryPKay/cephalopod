#include "Board.h"


Board::Board(int rowCount, int colCount)
{
	assert(colCount >= M_MIN && rowCount <= N_MAX);
	this->rowCount = rowCount;
	this->colCount = colCount;

	matrix.resize(rowCount, std::vector<int>(colCount, 0));
}

Board::~Board()
{
}

void Board::print()
{
	// Print header
	printColumnNumbers();
	printRowseparator();
	printRows();
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
			std::cout << intToSymbol(matrix[j][i]) << " | ";
		}
		printRowseparator();
	}
}

void Board::printRowseparator()
{
	std::cout << std::endl << "  ";
	for (int i = 0; i < colCount; ++i)
	{
		std::cout << " ---";
	}
	std::cout << std::endl;
}

char Board::intToSymbol(int value)
{
	switch (value)
	{
	case 0:
		return ' ';
	}
	return '?';
}
