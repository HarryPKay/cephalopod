#pragma once
#include "Common.h"
#include <map>

using namespace cephalopod;
using namespace std;

/*
 * =====================================================================================
 *       Struct:  Cell
 *  Description:  
 *
 * =====================================================================================
 */
struct Cell
{
	/* ====================  LIFECYCLE     ======================================= */
	Cell()
		: pip(NO_DICE), occupant(NO_COLOR)
	{
	} /* constructor */
	~Cell() = default; /* destructor */

	/* ====================  DATA MEMBERS  ======================================= */
	int32_t pip;
	PlayerColor occupant;
};
