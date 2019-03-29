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
	map<Direction, Cell*> getNeighbors(const Position origin);
	string getAdjacentInfo(Position position);
	bool isWithinBounds(Position position) const;
	bool setMove(Move move);
	void undoMove();
	bool isMoveValid(Move move, int& pipSum);
	bool isMoveValid(Move move);
	bool isCaptureValid(Move move, int & pipSum);
	bool mustCapture(Move move);
	bool isCellVacant(Position position);
	bool isBoardFull();
	Color getMajorityColor();
	int getTotalColorCount(Color color);
	string previousAdjacentInfo;
	vector<Move> getPossibleMoves(Color playerColor);
	Color findOpposition(Color playerColor);
private:
	int rowCount;
	int colCount;
	Matrix<Cell> matrix;
	vector<Matrix<Cell>> history;
	vector<Capture> captureCombintions;
};

