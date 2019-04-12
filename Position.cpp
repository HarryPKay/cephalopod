#include "Position.h"

bool operator==(const Position& left, const Position& right)
{
	return Position::compare(left, right) == 0;
}

bool operator!=(const Position& left, const Position& right)
{
	return Position::compare(left, right) != 0;
}

bool operator<(const Position& left, const Position& right)
{
	return Position::compare(left, right) < 0;
}

bool operator<=(const Position& left, const Position& right)
{
	return Position::compare(left, right) <= 0;
}

bool operator>(const Position& left, const Position& right)
{
	return Position::compare(left, right) > 0;
}

bool operator>=(const Position& left, const Position& right)
{
	return Position::compare(left, right) >= 0;
}

int Position::compare(const Position& left, const Position& right)
{
	if (left.row < right.row) return -1;

	if (left.row == right.row) {
		if (left.col < right.col) {
			return -1;
		}
		if (left.col == right.col) {
			return 0;
		}
	}

	return 1;
}
