#include "Position.h"

bool operator==(const Position& left, const Position& right)
{
	return left.row == right.row && left.col == right.col;
}

bool operator!=(const Position& left, const Position& right)
{
	return !(left == right);
}

bool operator<(const Position& left, const Position& right)
{
	if (left.row < right.row)
	{
		return true;
	}

	if (left.row == right.row)
	{
		return left.col < right.col;
	}

	return false;
}

bool operator<=(const Position& left, const Position& right)
{
	return left < right || left == right;
}

bool operator>(const Position& left, const Position& right)
{
	return !(left <= right);
}

bool operator>=(const Position& left, const Position& right)
{
	return left > right || left == right;
}
