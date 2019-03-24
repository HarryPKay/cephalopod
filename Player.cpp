#include "Player.h"



Player::Player(Color color)
	: color(color)
{
	allPossibleCaptures = generateCombinationsVaryingSize(directions, 2, 4);
}

Player::~Player()
{
}


vector<Move> Player::generatePossibleMoves(BoardModel* state)
{
	vector<Move> potentialMoves;
	Move move = { Position(0,0),color, vector<Direction>() };

	for (int i = 0; i < state->getRowCount(); ++i)
	{
		for (int j = 0; j < state->getColCount(); ++j)
		{
			move.position = Position(i, j);
			move.captureTargets.clear();

			if (state->isMoveValid(move))
			{
				potentialMoves.push_back(move);
			}

			for (int i = 0; i < allPossibleCaptures.size(); ++i)
			{
				move.captureTargets = allPossibleCaptures[i];

				if (state->isMoveValid(move))
				{
					potentialMoves.push_back(move);
				}
			}
		}
	}

	return potentialMoves;
}