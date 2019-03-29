#pragma once
#include "Common.h"

using namespace cephalopod;

struct Move
{
	typedef vector<Direction> Capture;
	Move(Position position, Color color, Capture captureDirections)
		: position(position), color(color), captureDirections(captureDirections) {};
	Position position;
	Color color;
	Capture captureDirections;
};