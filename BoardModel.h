#pragma once
#include <assert.h>
#include <iostream>
#include <stack>
#include <string>
#include "Cell.h"
#include "Common.h"
#include "Helpers.h"
#include "Move.h"

using namespace cephalopod;

class BoardModel
{
public:

	typedef vector<vector<Cell>> Grid;
	typedef vector<Direction> Captures;
	typedef map<Direction, Cell*> Neighbours;

	BoardModel();
	BoardModel(int rowCount, int colCount);
	~BoardModel();
	void undoMove();
	void initializePositionToNeighbourMapping();
	int getColCount();
	int getRowCount();
	int getTotalColorCount(Color color);
	int getCapturePipSum(Move move);
	bool isWithinBounds(Position position) const;
	bool isMoveValid(Move move);
	bool isCaptureValid(Move move);
	bool mustCapture(Move move);
	bool isCellVacant(Position position);
	bool isBoardFull();
	bool setMove(Move move);
	string getNeighboursInfo(Position position);
	Neighbours getNeighbors(const Position origin);
	Color getMajorityColor();
	Cell getCell(Position position);
	Cell* getCellPointer(Position position);
	vector<Move> getPossibleMoves(Color playerColor, Position position);
	vector<Move> getAllPossibleMoves(Color playerColor);
	Grid* getGrid();
	string previousNeighbourInfo;

private:

	int rowCount;
	int colCount;
	Grid grid;
	stack<Grid> gridHistory;
	vector<Captures> captureCombintions;
	map<Position, Neighbours> positionToNeighboursMap;
};

