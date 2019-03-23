#include <iostream>
#include <map>
#include "Board.h"
#include "Position.h"

// absolute
//typedef std::vector<std::vector<int>> VectorMatrix;
// relative
//typedef std::map<int, std::map<int, Analysis>> MapMatrix;

// Board has cells, cell has pointer to a map

int main()
{
	Board board(5,5);
	board.test();
	board.print();

	char keepOpen;
	std::cin >> keepOpen;
	return 0;
}