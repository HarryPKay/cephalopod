#include "BoardViewer.h"
#include <iostream>

BoardViewer::BoardViewer(BoardModel * board)
	: board_(board)
{
}

//TODO: figure out why this wants to be static
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
	for (auto i = 0; i < board_->getColCount(); ++i)
	{
		std::cout << (i + 1) << "   ";
	}
}

void BoardViewer::printRows() const
{
	for (auto i = 0; i < board_->getRowCount(); ++i)
	{
		std::cout << (i + 1) << " |";
		for (auto j = 0; j < board_->getColCount(); ++j)
		{
			const auto color = (*board_->getGrid())[i][j].getColor();
			const auto pip = (*board_->getGrid())[i][j].getPip();

			if (color == no_color)
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

void BoardViewer::printRowSeparator() const
{
	std::cout << std::endl << "  ";
	for (int i = 0; i < board_->getColCount(); ++i)
	{
		std::cout << " ---";
	}
	std::cout << std::endl;
}
