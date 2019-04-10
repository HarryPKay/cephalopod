#pragma once

namespace cephalopod
{
	const int ROW_MAX = 9;
	const int ROW_MIN = 3;
	const int COL_MAX = 9;
	const int COL_MIN = 3;
	const int MIN_PIP = 1;
	const int MAX_PIP = 6;
	const int MIN_CAPTURE_PIP = 2;
	const int NO_DICE = 0;
	const int REFRESH_PAGE_SIZE = 20;
	const int PLAYER_COUNT = 2;
	const int MIN_CAPTURE_SIZE = 2;
	const int CIN_IGNORE_BUFFER_SIZE = 256;

	enum Color
	{
		white,
		black,
		no_color
	};

	enum Direction
	{
		up,
		right,
		down,
		left,
		direction_size
	};

	enum GameState
	{
		settings,
		in_progress,
		end
	};

	enum AiAlgorithm
	{
		minimax,
		alphabeta,
		ai_algorithm_size
	};

	enum PlayerType
	{
		human_player,
		easy_computer,
		moderate_computer,
		hard_computer,
		player_type_size
	};
}
