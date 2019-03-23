#pragma once
#include <assert.h>
#include <iostream>
#include "Cell.h"
#include "Common.h"
//#define NDEBUG

//TODO: separate out gameViewer/gameController
using namespace cephalopod;


class Board
{
public:

	Board(int width, int height);
	~Board();
	void print();

	Cell getCell(const Position position);
	Cell* getCellPointer(const Position position);
	bool isWithinBounds(const Position position) const;
	map<Direction, Cell*> getAdjacenctCells(const Position origin);

private:

	int rowCount;
	int colCount;
	Matrix<Cell> matrix;

	void printColumnNumbers(); //const
	void printRows(); //const
	void printRowSeparator(); //const
};

