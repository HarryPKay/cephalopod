#pragma once
#include <vector>
#include <map>

namespace cephalopod
{
	using namespace std;

	template <typename T>
	using Matrix = vector<vector<T>>;

	const int N_MAX = 9;
	const int M_MIN = 3;
	const int MIN_PIP = 1;
	const int MAX_PIP = 6;
	const int NO_DICE = 0;
	const int ADJACENCY_MATRIX_SIZE = 3;
	const char MOVE_SEPARATOR = ' ';

	enum Color
	{
		white, black, noColor
	};

	enum Direction
	{
		up, right, down, left
	};

	struct Position
	{
		Position(int row, int col)
		{
			this->row = row;
			this->col = col;
		}
		int row;
		int col;
	};

	struct Move
	{
		Position position;
		Color color;
		vector<Direction> captureTargets;
	};
}