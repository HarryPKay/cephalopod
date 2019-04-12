#pragma once
#include <cstdint>

struct Position
{
	/* LIFECYCLE */

	Position(const uint32_t row, const uint32_t col)
		: row(row)
		  , col(col)
	{
	};

	/* OPERATORS */

	/*
	 * Position ordering from least to greatest:
	 * (col,row): (0,0) < (0,1) < (1,0) < (1,1)    
	 */
	friend bool operator==(const Position& left, const Position& right);
	friend bool operator!=(const Position& left, const Position& right);
	friend bool operator<(const Position& left, const Position& right);
	friend bool operator<=(const Position& left, const Position& right);
	friend bool operator>(const Position& left, const Position& right);
	friend bool operator>=(const Position& left, const Position& right);
	static int32_t compare(const Position& left, const Position& right);

	/* DATA MEMBERS */

	uint32_t row;
	uint32_t col;
};
