#pragma once
#include "Cell.h"
#include "Common.h"
#include "Move.h"
#include "Position.h"
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace cephalopod;

/*
 * =====================================================================================
 *        Class:  BoardModel
 *  Description:  
 *
 * =====================================================================================
 */
class BoardModel final
{
	typedef vector<vector<Cell>> Grid;
	typedef vector<Direction> Captures;
	typedef map<Direction, Cell*> Neighbors;

public:
	/* ====================  LIFECYCLE     ======================================= */
	BoardModel(); /* constructor */
	BoardModel(int rowCount, int colCount);
	~BoardModel() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	BoardModel(const BoardModel&) = delete; /* copy */
	BoardModel(BoardModel&&) = delete; /* move */

	/* ====================  ACCESSORS     ======================================= */
	int getColCount() const;
	int getRowCount() const;
	Cell getCell(Position position);
	Cell* getCellPointer(Position position);
	Grid* getGrid();
	Neighbors getNeighbors(Position origin);
	string getNeighborsInfo() const;

	/* ====================  MUTATORS      ======================================= */
	bool setMove(Move move);
	void undoMove();
	void initializePositionToNeighborMapping();
	void setNeighborsInfo(Position position);

	/* ====================  OPERATORS     ======================================= */
	BoardModel& operator=(const BoardModel&) = delete; /* copy assignment */
	BoardModel& operator=(BoardModel&&) = delete; /* move assignment */

	/* ====================  VALIDATORS    ======================================= */
	bool isWithinBounds(Position position) const;
	bool isCellVacant(Position position);
	bool isBoardFull();

	//TODO: Move the following into rules (maybe)
	bool isMoveValid(Move move);
	bool isCaptureValid(Move move);
	bool mustCapture(Move move);

	/* ====================  METHODS       ======================================= */
	int sumCellsWithColor(Color color);
	int sumPipForMove(Move move);
	Color findMajorityColor();

	//TODO: Move the following into rules (maybe)
	vector<Move> findPossibleMoves(Color playerColor, Position position);
	vector<Move> findAllPossibleMoves(Color playerColor);

private:
	/* ====================  DATA MEMBERS  ======================================= */
	int rowCount_;
	int colCount_;
	Grid grid_;
	stack<Grid> gridHistory_;
	vector<Captures> captureCombinations_;
	map<Position, Neighbors> positionToNeighborsMap_;
	string neighborInfo_;
}; /* -----  end of class BoardModel  ----- */
