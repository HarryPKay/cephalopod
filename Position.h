#pragma once

struct Position
{
	/* ====================  LIFECYCLE     ======================================= */
	Position(const int row, const int col)
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
	int row;
	int col;
};
