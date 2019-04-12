#pragma once
#include "Common.h"
#include "Position.h"
#include <utility>
#include <vector>

using namespace std;
using namespace cephalopod;

/*
 * Stores information about a move, such as where to move, what to capture and
 * who is capturing.
 */
struct Move
{
	typedef vector<Direction> Captures;

	/* LIFE CYCLE */

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

	/* DATA MEMBERS  */

	Position position; // Where to move
	PlayerColor color; // Who is capturing
	Captures captureDirections; // In which directions should neighbors be captured.
};
