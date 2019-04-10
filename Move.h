#pragma once
#include <utility>
#include "Common.h"
#include "Position.h"

using namespace cephalopod;

struct Move
{
	typedef vector<Direction> Captures;

	/* ==================== LIFE CYCLE     ======================================= */
	Move()
		: position(Position(-1, -1)), color(no_color), captureDirections(Captures()) {};
	
	Move(const Position position, const Color color, Captures captureDirections)
		: position(position), color(color), captureDirections(std::move(captureDirections)) {};

	/* ====================  DATA MEMBERS  ======================================= */
	Position position;
	Color color;
	Captures captureDirections;
};