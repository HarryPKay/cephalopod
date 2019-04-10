#include "Cell.h"
#include <cassert>

int Cell::getPip() const
{
	return pip_;
}

void Cell::setPip(const int value)
{
	assert(value >= 0 && value <= MAX_PIP);
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
