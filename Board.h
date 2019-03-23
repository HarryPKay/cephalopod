#pragma once
#include <assert.h>
#include <iostream>
#include "Constants.h"
#include "Position.h"
#include "Die.h"
//#define NDEBUG

//TODO: separate out gameViewer/gameController
using namespace cephalopod;
class Board
{
public:

	Board(int width, int height);
	~Board();
	void print();
	void test();

private:
	int rowCount;
	int colCount;
	Matrix<Die> matrix;

	void printColumnNumbers(); //const
	void printRows(); //const
	void printRowSeparator(); //const
	Die* getDiePtr(const Position position);
	AdjacencyMap<Die*> getAdjacencyMap(const Position origin);
};

