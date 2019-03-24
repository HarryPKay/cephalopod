#include "Player.h"



Player::Player(Color color)
	: color(color)
{
	allPossibleCaptures = generateCombinationsVaryingSize(directions, 2, 4);
}

Player::~Player()
{
}


vector<Move> Player::generatePossibleMoves(BoardModel* board, Color playerColor)
{
	vector<Move> potentialMoves;
	Move move = { Position(0,0), playerColor, vector<Direction>() };

	for (int i = 0; i < board->getRowCount(); ++i)
	{
		for (int j = 0; j < board->getColCount(); ++j)
		{
			move.position = Position(i, j);
			move.captureTargets.clear();

			if (board->isMoveValid(move))
			{
				potentialMoves.push_back(move);
			}

			for (int i = 0; i < allPossibleCaptures.size(); ++i)
			{
				move.captureTargets = allPossibleCaptures[i];

				if (board->isMoveValid(move))
				{
					potentialMoves.push_back(move);
				}
			}
		}
	}

	return potentialMoves;
}