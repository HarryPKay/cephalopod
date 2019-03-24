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


class BoardModel
{
public:
	BoardModel();
	BoardModel(int rowCount, int colCount);
	~BoardModel();
	Cell getCell(Position position);
	Cell* getCellPointer(Position position) ;
	int getColCount();
	int getRowCount();
	Matrix<Cell>* getMatrix();
	map<Direction, Cell*> getAdjacenctCells(const Position origin);
	string getAdjacentInfo(Position position);
	bool isWithinBounds(Position position) const;
	bool setMove(Move move);
	bool isMoveValid(Move move, int& pipSum);
	bool isMoveValid(Move move);
	bool isCaptureValid(Move move, int & pipSum);
	bool isCellVacant(Position position);
	bool isBoardFull();
	Color getMajorityColor();
	string previousAdjacentInfo;
private:
	int rowCount;
	int colCount;
	Matrix<Cell> matrix;
};

