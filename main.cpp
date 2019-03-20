#include <iostream>
#include "Board.h"

int main()
{
	Board board = Board(5, 5);
	board.print();
	char keepOpen;
	std::cin >> keepOpen;
	return 0;
}