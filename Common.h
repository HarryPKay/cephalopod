#pragma once
#include <cstdint>

namespace cephalopod
{
	const int32_t MIN_PIP = 1;
	const int32_t MAX_PIP = 6;
	const int32_t NO_DICE = 0;
	const uint32_t ROW_MAX = 9;
	const uint32_t ROW_MIN = 3;
	const uint32_t COL_MAX = 9;
	const uint32_t COL_MIN = 3;
	const uint32_t MIN_CAPTURE_PIP = 2;
	const uint32_t REFRESH_PAGE_SIZE = 20;
	const uint32_t PLAYER_COUNT = 2;
	const uint32_t MIN_CAPTURE_SIZE = 2;
	const uint32_t MAX_CAPTURE_SIZE = 4;
	const uint32_t CIN_IGNORE_BUFFER_SIZE = 256;
	const uint32_t MIN_DEPTH_SEARCH = 2;

	enum PlayerColor
	{
		WHITE,
		BLACK,
		NO_COLOR
	};

	enum Direction
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		DIRECTION_SIZE
	};

	enum GameState
	{
		SETTINGS,
		IN_PROGRESS,
		END
	};

	enum AiAlgorithm
	{
		MINIMAX,
		ALPHABETA,
		AI_ALGORITHM_SIZE
	};

	enum PlayerType
	{
		HUMAN_PLAYER,
		EASY_COMPUTER,
		MODERATE_COMPUTER,
		HARD_COMPUTER,
		PLAYER_TYPE_SIZE
	};
}
