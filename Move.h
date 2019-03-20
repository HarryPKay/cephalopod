#pragma once
#include "Color.h"
#include "Position.h"

struct Move
{
	Position position;
	Color color;
	bool isIntentCapture;
};