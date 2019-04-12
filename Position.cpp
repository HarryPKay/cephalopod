#include "Position.h"


int32_t compare(const Position& left, const Position& right)
{
	if (left.row < right.row) return -1;
	
	if (left.row == right.row) {
		if (left.col < right.col) {
			return -1;
		}
		if(left.col == right.col) {
			return 0;
		}
	}

	return 1;
}

bool operator==(const Position& left, const Position& right)
{
	return compare(left, right) == 0;
	//return left.row == right.row && left.col == right.col;
}

bool operator!=(const Position& left, const Position& right)
{
	return compare(left, right) != 0;
	//return !(left == right);
}

bool operator<(const Position& left, const Position& right)
{
	return compare(left, right) < 0;
	//if (left.row < right.row)
	//{
	//	return true;
	//}

	//if (left.row == right.row)
	//{
	//	return left.col < right.col;
	//}

	//return false;
}

bool operator<=(const Position& left, const Position& right)
{
	return compare(left, right) <= 0;
	/*return left < right || left == right;*/
}

bool operator>(const Position& left, const Position& right)
{
	return compare(left, right) > 0;
	//return !(left <= right);
}

bool operator>=(const Position& left, const Position& right)
{
	return compare(left, right) >= 0;
	//return left > right || left == right;
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
