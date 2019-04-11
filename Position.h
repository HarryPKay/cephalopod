#pragma once
#include <cstdint>

struct Position
{
	/* ====================  LIFECYCLE     ======================================= */
	Position(const uint32_t row, const uint32_t col)
		: row(row)
		  , col(col)
	{
	};

	/* ====================  OPERATORS     ======================================= */
	friend bool operator==(const Position& left, const Position& right);
	friend bool operator!=(const Position& left, const Position& right);
	friend bool operator<(const Position& left, const Position& right);
	friend bool operator<=(const Position& left, const Position& right);
	friend bool operator>(const Position& left, const Position& right);
	friend bool operator>=(const Position& left, const Position& right);

	/* ====================  DATA MEMBERS  ======================================= */
	uint32_t row;
	uint32_t col;
};
