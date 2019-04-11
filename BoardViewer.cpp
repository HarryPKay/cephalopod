#include "BoardViewer.h"
#include <iostream>

BoardViewer::BoardViewer(BoardModel* board)
	: board_(board)
{
}

void BoardViewer::refreshConsole() const
{
	string buffer;
	for (auto i = 0; i < REFRESH_PAGE_SIZE; ++i)
	{
		buffer.append("\n");
	}
	cout << buffer;
}

void BoardViewer::renderBoardToConsole() const
{
	refreshConsole();
	printColumnNumbers();
	printRowSeparator();
	printRows();
	cout << board_->getNeighborsInfo();
}

void BoardViewer::printColumnNumbers() const
{
	std::cout << "    ";
	for (uint32_t i = 0; i < board_->getColCount(); ++i)
	{
		std::cout << (i + 1) << "   ";
	}
}

void BoardViewer::printRows() const
{
	for (uint32_t i = 0; i < board_->getRowCount(); ++i)
	{
		std::cout << (i + 1) << " |";
		for (uint32_t j = 0; j < board_->getColCount(); ++j)
		{
			const auto color = (*board_->getGrid())[i][j].getOccupantColor();
			const auto pip = (*board_->getGrid())[i][j].getPip();

			if (color == NO_COLOR)
			{
				std::cout << "   |";
			}
			else if (color == WHITE)
			{
				std::cout << " " << pip << " |";
			}
			else if (color == BLACK)
			{
				std::cout << "-" << pip << " |";
			}
			else
			{
				std::cout << " ?"
					<< " |";
			}
		}

		printRowSeparator();
	}
}

void BoardViewer::printRowSeparator() const
{
	std::cout << std::endl
		<< "  ";
	for (uint32_t i = 0; i < board_->getColCount(); ++i)
	{
		std::cout << " ---";
	}
	std::cout << std::endl;
}
