#pragma once
#include "Common.h"
#include <map>

using namespace cephalopod;
using namespace std;

/*
 * =====================================================================================
 *        Class:  Cell
 *  Description:  
 *
 * =====================================================================================
 */
class Cell final
{
	typedef map<Direction, Cell*> Neighbors;

public:
	/* ====================  LIFECYCLE     ======================================= */
	Cell() = default; /* constructor */
	~Cell() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	Cell(const Cell&) = default; /* copy */
	Cell(Cell&&) = default; /* move */

	/* ====================  ACCESSORS     ======================================= */
	int32_t getPip() const;
	PlayerColor getOccupantColor() const;

	/* ====================  MUTATORS      ======================================= */
	void setPip(int32_t value);
	void setOccupantColor(PlayerColor occupant);
	void capture();

	/* ====================  OPERATORS     ======================================= */
	Cell& operator=(const Cell&) = default; /* copy assignment */
	Cell& operator=(Cell&&) = default; /* move assignment */

private:
	/* ====================  DATA MEMBERS  ======================================= */
	int32_t pip_ = NO_DICE;
	PlayerColor occupant_ = NO_COLOR;
}; /* -----  end of class Cell  ----- */
