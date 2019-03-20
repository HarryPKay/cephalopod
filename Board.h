#pragma once
#include <assert.h>
#include <map>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "Position.h"
//#define NDEBUG

typedef std::vector<std::vector<int>> Matrix;

class Board
{
public:
	Board(int width, int height);
	~Board();
	void print();

private:
	int rowCount;
	int colCount;
	Matrix matrix;
	void printColumnNumbers();
	void printRows();
	void printRowseparator();
	char intToSymbol(int value);
};

