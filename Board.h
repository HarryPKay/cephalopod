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
	Board(int rowCount, int colCount);
	~Board();
	Cell getCell(Position position);
	Cell* getCellPointer(Position position) ;
	int getColCount();
	int getRowCount();
	Matrix<Cell>* getMatrix();
	map<Direction, Cell*> getAdjacenctCells(const Position origin);
	bool isWithinBounds(Position position) const;
	void refreshPage() const;
	void print();
	void printColumnNumbers();
	void printRows();
	void printRowSeparator();
	bool setMove(Move move);
	bool isBoardFull();
	Color getMajorityColor();

private:
	int rowCount;
	int colCount;
	Matrix<Cell> matrix;
};

