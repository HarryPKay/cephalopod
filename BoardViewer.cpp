#include "BoardViewer.h"



BoardViewer::BoardViewer()
{
}

BoardViewer::BoardViewer(BoardModel * board)
	: board(board)
{
}

BoardViewer::~BoardViewer()
{
}


void BoardViewer::refreshConsole() const
{
	//cout << string("\n", REFRESH_PAGE_SIZE);
}

void BoardViewer::renderBoardToConsole()
{
	refreshConsole();
	printColumnNumbers();
	printRowSeparator();
	printRows();
	cout << board->previousNeighbourInfo;
}

void BoardViewer::printColumnNumbers()
{
	std::cout << "    ";
	for (int i = 0; i < board->getColCount(); ++i)
	{
		std::cout << (i + 1) << "   ";
	}
}

void BoardViewer::printRows()
{
	for (int i = 0; i < board->getRowCount(); ++i)
	{
		std::cout << (i + 1) << " |";
		for (int j = 0; j < board->getColCount(); ++j)
		{
			Color color = (*board->getGrid())[i][j].getColor();
			int pip = (*board->getGrid())[i][j].getPip();

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

void BoardViewer::printRowSeparator()
{
	std::cout << std::endl << "  ";
	for (int i = 0; i < board->getColCount(); ++i)
	{
		std::cout << " ---";
	}
	std::cout << std::endl;
}
