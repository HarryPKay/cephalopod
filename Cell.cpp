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

void Cell::setOccupant(Color occupant)
{
	this->occupant = occupant;
}

void Cell::capture()
{
	occupant = noColor;
	pip = 0;
}