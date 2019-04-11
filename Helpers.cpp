#include "Helpers.h"
#include <iostream>

namespace cephalopod
{
	using namespace std;

	string directionEnumToString(const Direction direction)
	{
		switch (direction)
		{
		case UP: return "up";
		case RIGHT: return "right";
		case DOWN: return "down";
		case LEFT: return "left";
		default: return "";
		}
	}

	string playerColorEnumToString(const PlayerColor playerColor)
	{
		switch (playerColor)
		{
		case WHITE: return "white";
		case BLACK: return "black";
		case NO_COLOR: return "no playerColor";
		default: return "";
		}
	}

	string playerTypeEnumToString(const PlayerType playerType)
	{
		switch (playerType)
		{
		case HUMAN_PLAYER: return "Human Player";
		case EASY_COMPUTER: return "Easy Computer";
		case MODERATE_COMPUTER: return "Moderate Computer";
		case HARD_COMPUTER: return "Hard Computer";
		default: return "";
		}
	}

	string aiAlgorithmEnumToString(const AiAlgorithm aiAlgorithm)
	{
		switch (aiAlgorithm)
		{
		case MINIMAX: return "MiniMax";
		case ALPHABETA: return "AlphaBeta";
		default: return "";
		}
	}

	PlayerColor findOpposition(const PlayerColor playerColor)
	{
		if (playerColor == WHITE)
		{
			return BLACK;
		}
		return WHITE;
	}


	void promptForInteger(uint32_t& value)
	{
		cin >> value;

		while (cin.fail())
		{
			cout << "Integers accepted only." << std::endl;
			cin.clear();
			cin.ignore(CIN_IGNORE_BUFFER_SIZE, '\n');
			cout << "> ";
			cin >> value;
		}
	}

	void promptForInteger(uint32_t& valueA, uint32_t& valueB)
	{
		cin >> valueA >> valueB;

		while (cin.fail())
		{
			cout << "Integers accepted only." << std::endl;
			cin.clear();
			cin.ignore(CIN_IGNORE_BUFFER_SIZE, '\n');
			cout << "> ";
			cin >> valueA >> valueB;
		}
	}
}
