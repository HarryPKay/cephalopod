#include "RandomPlayer.h"



RandomPlayer::~RandomPlayer()
{
}

Move RandomPlayer::getMove()
{
	int col = 0;
	int row = 0;
	Cell* cell = nullptr;
	Move move = { Position(0,0) , color, vector<Direction>() };

	do
	{
		vector<Direction> potentialTargets;

		row = rand() % board->getRowCount();
		col = rand() % board->getColCount();
		move.position = Position(row, col);

		cell = board->getCellPointer(move.position);
		map<Direction, Cell*> adjacentCells = cell->getAdjacentCells();

		for (int i = 0; i < (int)Direction::size; ++i)
		{
			Cell* adjacentCell = adjacentCells[(Direction)i];

			if (adjacentCell != nullptr
				&& adjacentCell->getColor() != noColor
				&& adjacentCell->getColor() != color)
			{
				potentialTargets.push_back((Direction)i);
			}
		}

		int temp = 0;
		move.captureTargets = potentialTargets;

		if (!board->isCaptureValid(move, temp))
		{
			move.captureTargets.clear();
		}
	}
	while (!board->isMoveValid(move));
	
	return move;
}
