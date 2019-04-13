#pragma once
#include "Common.h"
#include "Position.h"
#include <utility>
#include <vector>

using namespace std;
using namespace cephalopod;

/*
 * Stores information about a move.
 */
struct Move
{
	typedef vector<Direction> Captures;

	/* LIFE CYCLE */

	Move()
		: position(Position(0, 0))
		  , color(NO_COLOR)
		  , captureDirections(Captures())
		  , pipSum(MIN_PIP)
	{
	};

	Move(const Position position, const PlayerColor color, Captures captureDirections, const int32_t pipSum)
		: position(position)
		  , color(color)
		  , captureDirections(std::move(captureDirections))
		  , pipSum(pipSum)
	{
	};

	/* DATA MEMBERS  */

	Position position; // Where to move.
	PlayerColor color; // Who is capturing.
	Captures captureDirections; // In which directions should neighbors be captured.
	int32_t pipSum; // What value to place in the targeted cell/
};
