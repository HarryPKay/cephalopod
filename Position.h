#pragma once

struct Position
{
	Position(int row, int col)
	{
		this->row = row;
		this->col = col;
	}
	int row;
	int col;
};