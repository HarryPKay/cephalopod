#pragma once
#include <assert.h>
#include <iostream>
#include <string>
#include "Cell.h"
#include "Common.h"
#include "Helpers.h"
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
	Neighbours getAdjacenctCells(const Position origin);
	bool isWithinBounds(Position position) const;
	void refreshPage() const;
	void print();
	void printColumnNumbers();
	void printRows();
	void printRowSeparator();
	string getNeighboursInfo(Position position);
	bool setMove(Move move);
	bool isMoveValid(Move move, int& pipSum);
	bool isMoveValid(Move move);
	bool isCaptureValid(Move move, int & pipSum);
	bool isCellVacant(Position position);
	bool isBoardFull();
	Color getMajorityColor();

private:
	int rowCount;
	int colCount;
	Matrix<Cell> grid;
	string previousNeighbourInfo;
};

