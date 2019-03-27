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
	//TODO: validate pip under 7 above 0
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

void Cell::capture()
{
	occupant = noColor;
	pip = 0;
}