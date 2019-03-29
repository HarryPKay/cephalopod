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
	void setPip(int value);
	void setOccupant(Color occupant);
	void capture();
	int getPip();
	Color getColor();

private:

	int pip = NO_DICE;
	Color occupant = noColor;
};

