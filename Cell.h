#pragma once
#include <iostream>
#include "Common.h"

using namespace cephalopod;
using namespace std;

// TODO: find out if it is ok to init map before occupation.
class Cell
{
public:

	typedef map<Direction, Cell*> Neighbours;

	Cell();
	~Cell();
	int getPip();
	void setPip(int value);
	Color getColor();
	void setColor(Color value);
	Neighbours getNeighbours();
	void setNeighbors(Neighbours value);
	void capture();
private:
	int pip = NO_DICE;
	Neighbours adjacentCells;
	Color occupant = noColor;
};

