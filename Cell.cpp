#include "Cell.h"


Cell::Cell()
{
}

Cell::~Cell()
{
}

int Cell::getPip()
{
	return pip;
}

void Cell::setPip(int value)
{
	//TODO: pip under 7 above 0
	pip = value;
}

Color Cell::getColor()
{
	return occupant;
}

void Cell::setColor(Color value)
{
	occupant = value;
}

map<Direction, Cell*> Cell::getAdjacentCells()
{
	return  adjacentCells;
}

void Cell::setAdjacentCells(map<Direction, Cell*> value)
{
	this->adjacentCells = value;
}

// TODO make better.
void Cell::printAdjacentInfo()
{
	for (int i = 0; i < 4; ++i)
	{
		cout << i;
		if (black == adjacentCells[Direction(i)]->getColor())
		{
			cout << " -";
		}
		else
		{
			cout << " ";
		}
		cout << adjacentCells[Direction(i)]->getPip() << endl;
	}
}
