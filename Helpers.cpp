#include "Helpers.h"

namespace cephalopod
{
	using namespace std;

	string directionEnumToString(const Direction direction)
	{
		switch (direction)
		{
		case up:
			return "up";
		case right:
			return "right";
		case down:
			return "down";
		case left:
			return "left";
		default: ;
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

	string playerTypeEnumToString(const PlayerType playerType)
	{
		switch (playerType)
		{
		case human_player: return "Human Player";
		case easy_computer: return "Easy Computer";
		case moderate_computer: return "Moderate Computer";
		case hard_computer: return "Hard Computer";
		default: return  "";
		}
	}

	string aiAlgorithmEnumToString(const AiAlgorithm aiAlgorithm)
	{
		switch (aiAlgorithm)
		{
			case minimax: return "MiniMax";
		case alphabeta: return "AlphaBeta";
		default: return "";
		}
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
