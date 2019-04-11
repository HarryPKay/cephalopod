#pragma once
#include "Common.h"
#include "Position.h"
#include <utility>
#include <vector>

using namespace  std;
using namespace cephalopod;

struct Move
{
	typedef vector<Direction> Captures;

	/* ==================== LIFE CYCLE     ======================================= */
	Move()
		: position(Position(0, 0))
		  , color(NO_COLOR)
		  , captureDirections(Captures())
	{
	};

	Move(const Position position, const PlayerColor color, Captures captureDirections)
		: position(position)
		  , color(color)
		  , captureDirections(std::move(captureDirections))
	{
	};

	/* ====================  DATA MEMBERS  ======================================= */
	Position position;
	PlayerColor color;
	Captures captureDirections;
};
