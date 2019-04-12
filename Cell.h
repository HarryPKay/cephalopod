#pragma once
#include "Common.h"
#include <map>

using namespace cephalopod;
using namespace std;

/*
 * Provides the data that represents a dice or lack of dice.
 */
struct Cell
{
	/* LIFECYCLE */

	Cell()
		: pip(NO_DICE), occupant(NO_COLOR)
	{
	} /* constructor */
	Cell(const Cell&) = default; /* copy */
	Cell(Cell&&) = default; /* move */
	~Cell() = default; /* destructor */

	/* OPERATORS */

	Cell& operator=(const Cell&) = default; /* copy assignment */
	Cell& operator=(Cell&&) = default; /* move assignment */

	/* DATA MEMBERS */

	int32_t pip;

	// The color of who owns this cell/dice.
	PlayerColor occupant;
};
