#pragma once
#include "BoardModel.h"
#include "Common.h"

using namespace cephalopod;
using namespace std;

/*
 * Provides the representation of the board to the user.
 */
class BoardViewer final
{
public:

	/* LIFECYCLE */

	BoardViewer() = default; /* constructor */
	BoardViewer(BoardModel* board);
	BoardViewer(const BoardViewer&) = delete; /* copy */
	BoardViewer(BoardViewer&&) = delete; /* move */
	~BoardViewer() = default; /* destructor */

	/* OPERATORS */

	BoardViewer& operator=(const BoardViewer&) = delete; /* copy assignment */
	BoardViewer& operator=(BoardViewer&&) = delete; /* move assignment */

	/* METHODS */

	/*
	 * Prints out a text based representation of the board and it's dice.
	 */
	void renderBoardToConsole() const;

private:

	/* METHODS */

	/*
	 * Prints out the numbered column guides for the board.
	 */
	void printColumnNumbers() const;

	/*
	 * Prints out each row with it's row number, dice and partitions separating
	 * each column.
	 */
	void printRows() const;

	/*
	 * Prints the partitions separating each row.
	 */
	void printRowSeparator() const;

	/* DATA MEMBERS */

	BoardModel* board_;
};
