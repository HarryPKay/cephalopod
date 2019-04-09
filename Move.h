#pragma once
#include "Common.h"

using namespace cephalopod;

struct Move
{
	typedef vector<Direction> Captures;
	Move()
		: position(Position(-1, -1)), color(noColor), captureDirections(Captures()) {};

	Move(Position position, Color color, Captures captureDirections)
		: position(position), color(color), captureDirections(captureDirections) {};
	Position position;
	Color color;
	Captures captureDirections;
};