#include "Cell.h"
#include <cassert>

int32_t Cell::getPip() const
{
	return pip_;
}

void Cell::setPip(const int32_t value)
{
	assert(value >= 0 && value <= WHITE_MAX_PIP);
	pip_ = value;
}

PlayerColor Cell::getOccupantColor() const
{
	return occupant_;
}

void Cell::setOccupantColor(const PlayerColor occupant)
{
	this->occupant_ = occupant;
}

void Cell::capture()
{
	occupant_ = NO_COLOR;
	pip_ = 0;
}
