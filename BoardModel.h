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
 * Represents a board where dice can be placed. Provides checks to ensure that the
 * board is in a consistent, however, does not hold any game logic.
 */
class BoardModel final
{
	/* TYPEDEFS */

	typedef vector<Direction> Captures;
	typedef vector<vector<Cell>> Grid;
	typedef map<Direction, Cell*> Neighbors;

public:

	/* LIFECYCLE */

	BoardModel() = delete; /* constructor */
	BoardModel(uint32_t rowCount, uint32_t colCount);
	BoardModel(const BoardModel&) = delete; /* copy */
	BoardModel(BoardModel&&) = delete; /* move */
	~BoardModel() = default; /* destructor */

	/* OPERATORS */

	BoardModel& operator=(const BoardModel&) = delete; /* copy assignment */
	BoardModel& operator=(BoardModel&&) = delete; /* move assignment */

	/* ACCESSORS */

	uint32_t getColCount() const;
	uint32_t getRowCount() const;
	Cell getCell(Position position);
	Cell* getCellPointer(Position position);
	Neighbors getNeighbors(Position origin);
	string getNeighborsInfo() const;

	/* MUTATORS */

	/*
	 * Carries out the instructions that modifies the board, given by move.
	 *
	 * @param move A struct that holds information such as where to place the dice,
	 * what color is that dice, 2nd what cells should be captured.
	 * @param pip The value of the cell being occupied, found by GameAnalyzer.
	 * @return The boolean value indicating the success to alter the state of the
	 * board. 
	 *
	 * Pre-condition:
	 * - A copy of the grid_ is pushed back on gridHistory_ at the start of the
	 * - function call.
	 * - neighborsInfo is set at the start of the function call.
	 * - The move is valid by the game rules as dictated by the GameAnalyzer class.
	 * - A valid pip given that equals the value of all neighbors to be captured.
	 *
	 * Post-condition:
	 * - Cell at move.position set to the given pip.
	 * - Neighbor's pip counts set to 0 for each capture in move.
	 * - Neighbor's occupant is set to NO_COLOR for each capture in move.
	 */
	bool setMove(Move move);

	/*
	 * Rewinds the board state by one move, undoing the last setMove() call.
	 * 
	 * Pre-condition:
	 * gridHistory_ is non zero
	 * 
	 * Post-condition:
	 * - grid_ holds the deleted top value of gridHistory
	 */
	void undoMove();

	/*
	 * For each cell within grid_, ensures that there is a mapping between that
	 * position and a map of pointers to cells that is that position's neighbors.
	 *
	 * Post-condition:
	 * - positionToNeighborsMap_ is the same size of grid_ and it's neighbor data
	 * points to existing neighboring cells.
	 */
	void initializePositionToNeighborMapping();

	/*
	 * Records the previous state of the neighbors for a given position.
	 *
	 * @param position The cell for which neighbor information should be recorded.
	 * 
	 * Post-condition:
	 * neighborsInfo_ string set with the neighbor information.
	 */
	void setNeighborsInfo(Position position);

	/* VALIDATORS */

	/*
	 * Checks whether the given position holds a location that exists on grid_
	 * 
	 * @param position The position for which to check
	 * @return True if the grid_ does have such a position.
	 */
	bool isWithinBounds(Position position) const;

	/*
	 * Checks whether the position is not occupied.
	 * 
	 * Pre-condition:
	 * - The targeted cell actually exists.
	 * 
	 * @param position The position to check
	 * @return The boolean value indicating if the cell is vacant.
	 */
	bool isCellVacant(Position position);

	/*
	 * Checks whether all cells have been occupied.
	 * 
	 * @return The boolean value indicating if the board is full.
	 */
	bool isBoardFull();

private:

	/*  DATA MEMBERS  */

	uint32_t rowCount_{};
	uint32_t colCount_{};

	// Holds all the cells.
	Grid grid_;

	// Tracks previous states of the grid_.
	stack<Grid> gridHistory_;

	// Provides the mapping between each position on the board and pointers to it's
	// corresponding neighbors.
	map<Position, Neighbors> positionToNeighborsMap_;

	// Provides information on the last move's neighbor's previous state.
	string neighborInfo_;
};
