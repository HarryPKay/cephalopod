#pragma once
#include <iostream>
#include "Common.h"

using namespace cephalopod;
using namespace std;

// TODO: find out if it is ok to init map before occupation.
class Cell
{
public:
	Cell();
	~Cell();
	int getPip();
	void setPip(int value);
	Color getColor();
	void setColor(Color value);
	map<Direction, Cell*> getAdjacentCells();
	void setAdjacentCells(map<Direction, Cell*> value);
	void printAdjacentInfo();
private:
	int pip = NO_DICE;
	bool isTouched = false;
	map<Direction, Cell*> adjacentCells;
	Color occupant = noColor;
};

