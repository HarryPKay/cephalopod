#include "Cell.h"


int Cell::getPip() const
{
	return pip_;
}

void Cell::setPip(const int value)
{
	//TODO: validate pip under 7 above 0
	pip_ = value;
}

Color Cell::getColor() const
{
	return occupant_;
}

void Cell::setOccupant(const Color occupant)
{
	this->occupant_ = occupant;
}

void Cell::capture()
{
	occupant_ = no_color;
	pip_ = 0;
}