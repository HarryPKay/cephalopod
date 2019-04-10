#pragma once
#include <map>
#include "Common.h"

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
        Cell() = default;                        /* constructor */
        ~Cell() = default;                       /* destructor */

        /* ====================  SPECIAL       ======================================= */
        Cell(const Cell&) = default;              /* copy */
        Cell(Cell&&) = default;                   /* move */

        /* ====================  ACCESSORS     ======================================= */
		int getPip() const;
		Color getColor() const;

        /* ====================  MUTATORS      ======================================= */
		void setPip(int value);
		void setOccupant(Color occupant);
		void capture();

        /* ====================  OPERATORS     ======================================= */
        Cell& operator=(const Cell&) = default;   /* copy assignment */
        Cell& operator=(Cell&&) = default;        /* move assignment */

    private:
        /* ====================  DATA MEMBERS  ======================================= */
		int pip_ = NO_DICE;
		Color occupant_ = no_color;
}; /* -----  end of class Cell  ----- */