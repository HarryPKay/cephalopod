#include "Helpers.h"

namespace cephalopod
{
	using namespace std;

	string directionEnumToString(Direction direction)
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
		}
		return "";
	}

	string colorEnumToString(Color color)
	{
		switch (color)
		{
		case white:
			return "white";
		case black:
			return "black";
		case noColor:
			return "no color";
		}
	}

	Color findOpposition(Color playerColor)
	{
		if (playerColor == white)
		{
			return black;
		}
		return white;
	}
}
