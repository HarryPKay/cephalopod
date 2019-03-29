#pragma once
#include <iostream>
#include "BoardModel.h"
#include "Common.h"

using namespace cephalopod;
using namespace std;

class BoardViewer
{
public:

	BoardViewer();
	BoardViewer(BoardModel* board);
	~BoardViewer();
	void renderBoardToConsole();
	void refreshConsole() const;
private:

	BoardModel* board;
	void printColumnNumbers();
	void printRows();
	void printRowSeparator();
};

