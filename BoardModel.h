#pragma once
#include <assert.h>
#include <iostream>
#include <string>
#include "Cell.h"
#include "Common.h"
#include "Helpers.h"
#include "Move.h"
//#define NDEBUG

//TODO: separate out gameViewer/gameController
using namespace cephalopod;

class BoardModel
{
public:

	typedef vector<vector<Cell>> Grid;
	typedef vector<Direction> Capture;
	typedef map<Direction, Cell*> Neighbours;

	BoardModel();
	BoardModel(int rowCount, int colCount);
	~BoardModel();
	Cell getCell(Position position);
	Cell* getCellPointer(Position position);
	int getColCount();
	int getRowCount();
	Grid* getGrid();
	Neighbours getNeighbors(const Position origin);
	string getNeighboursInfo(Position position);
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
	string previousNeighbourInfo;
	vector<Move> getPossibleMoves(Color playerColor);
	Color findOpposition(Color playerColor);
private:

	int rowCount;
	int colCount;
	Grid grid;
	vector<Grid> history;
	vector<Capture> captureCombintions;
	map<Position, Neighbours> positionToNeighboursMap;
};

