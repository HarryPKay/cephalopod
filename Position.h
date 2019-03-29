#pragma once
struct Position
{
	Position(int row, int col)
		: row(row), col(col) {};
	int row;
	int col;

	friend bool operator==(const Position &left, const Position &right);
	friend bool operator!=(const Position &left, const Position &right);
	friend bool operator<(const Position &left, const Position &right);
	friend bool operator<=(const Position &left, const Position &right);
	friend bool operator>(const Position &left, const Position &right);
	friend bool operator>=(const Position &left, const Position &right);
};

