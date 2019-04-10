#include "Helpers.h"

namespace cephalopod
{
	using namespace std;

	string directionEnumToString(const Direction direction)
	{
		switch (direction)
		{
		case cephalopod::up:
			return "up";
		case cephalopod::right:
			return "right";
		case cephalopod::down:
			return "down";
		case cephalopod::left:
			return "left";
		default:;
		}
		return "";
	}

	string colorEnumToString(const Color color)
	{
		switch (color)
		{
		case white:
			return "white";
		case black:
			return "black";
		case no_color:
			return "no color";
		}
		return {};
	}

	Color findOpposition(const Color playerColor)
	{
		if (playerColor == white)
		{
			return black;
		}
		return white;
	}
}
