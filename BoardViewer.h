#pragma once
#include "BoardModel.h"
#include "Common.h"

using namespace cephalopod;
using namespace std;

/*
 * =====================================================================================
 *        Class:  BoardViewer
 *  Description:  
 * =====================================================================================
 */
class BoardViewer final
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
		BoardViewer() = default;								/* constructor */
		BoardViewer(BoardModel* board);
        ~BoardViewer() = default;                       /* destructor */

        /* ====================  SPECIAL       ======================================= */
        BoardViewer(const BoardViewer&) = delete;              /* copy */
        BoardViewer(BoardViewer&&) = delete;                   /* move */

        /* ====================  OPERATORS     ======================================= */
        BoardViewer& operator=(const BoardViewer&) = delete;   /* copy assignment */
        BoardViewer& operator=(BoardViewer&&) = delete;        /* move assignment */

        /* ====================  METHODS       ======================================= */
		void renderBoardToConsole() const;

    private:
        /* ====================  METHODS       ======================================= */
		void printColumnNumbers() const;
		void printRows() const;
		void printRowSeparator() const;
		void refreshConsole() const;

        /* ====================  DATA MEMBERS  ======================================= */
		BoardModel* board_;

}; /* -----  end of class BoardViewer  ----- */