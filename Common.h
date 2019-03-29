#pragma once
#include <vector>
#include <map>

namespace cephalopod
{
	using namespace std;
	
	const int N_MAX = 9;
	const int M_MIN = 3;
	const int MIN_PIP = 1;
	const int MAX_PIP = 6;
	const int MIN_CAPTURE_PIP = 2;
	const int NO_DICE = 0;
	const int REFRESH_PAGE_SIZE = 1;
	const int PLAYER_COUNT = 2;
	//const char MOVE_SEPARATOR = ' ';

	enum Color
	{
		white, black, noColor
	};

	enum Direction
	{
		up, right, down, left, size
	};

	enum GameState
	{
		settings, inProgress, end
	};

	enum AIAlgorithm
	{
		minimax, alphabeta
	};

	enum PlayerType
	{
		human, easyComputer, hardComputer
	};

	struct Position
	{
		Position(int row, int col)
			: row(row), col(col) {};
		int row;
		int col;
	};

	typedef vector<Direction> Capture;
	struct Move
	{
		Move(Position position, Color color, Capture captures)
			: position(position), color(color), captures(captures) {};
		Position position;
		Color color;
		Capture captures;
	};
}