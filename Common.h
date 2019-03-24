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
	const int MIN_CAPTURE_PIP = 2;
	const int NO_DICE = 0;
	const char MOVE_SEPARATOR = ' ';
	const int REFRESH_PAGE_SIZE = 1;

	enum Color
	{
		white, black, noColor
	};

	enum Direction
	{
		up, right, down, left, size
	};

	const vector<Direction> directions = {
	Direction::up,
	Direction::right,
	Direction::down,
	Direction::left
	};

	enum GameState
	{
		settings, inProgress, end
	};

	struct Position
	{
		Position(int row, int col)
			: row(row), col(col) {};
		int row;
		int col;
	};

	struct Move
	{
		Move(Position position, Color color, vector<Direction> captureTargets)
			: position(position), color(color), captureTargets(captureTargets) {};
		Position position;
		Color color;
		vector<Direction> captureTargets;
	};

	struct BestMove
	{
		BestMove(Move move, int score)
			: move(move), score(score) {};
		Move move;
		float score;
	};
}