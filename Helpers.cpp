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

	Color findOpposition(Color playerColor)
	{
		if (playerColor == white)
		{
			return black;
		}
		return white;
	}
}
