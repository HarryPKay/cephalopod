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
	BoardModel() = delete; /* constructor */
	BoardModel(uint32_t rowCount, uint32_t colCount);
	~BoardModel() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	BoardModel(const BoardModel&) = delete; /* copy */
	BoardModel(BoardModel&&) = delete; /* move */

	/* ====================  ACCESSORS     ======================================= */
	uint32_t getColCount() const;
	uint32_t getRowCount() const;
	Cell getCell(Position position);
	Cell* getCellPointer(Position position);
	Grid* getGrid();
	Neighbors getNeighbors(Position origin);
	string getNeighborsInfo() const;


	/* ====================  MUTATORS      ======================================= */
	bool setMove(Move move, int32_t pip);
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

private:
	/* ====================  DATA MEMBERS  ======================================= */
	uint32_t rowCount_{};
	uint32_t colCount_{};
	Grid grid_;
	stack<Grid> gridHistory_;
	vector<Captures> captureCombinations_;
	map<Position, Neighbors> positionToNeighborsMap_;
	string neighborInfo_;
}; /* -----  end of class BoardModel  ----- */
