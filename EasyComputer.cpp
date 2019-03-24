#include "EasyComputer.h"



EasyComputer::~EasyComputer()
{
}

Move EasyComputer::getMove()
{
	vector<Move> potentialMoves = generatePossibleMoves(board);
	if (potentialMoves.size() == 0)
	{
		cout << " ahh\n";
		char keepOpen;
		cin >> keepOpen;
	}
	return potentialMoves[rand() % potentialMoves.size()];
}
