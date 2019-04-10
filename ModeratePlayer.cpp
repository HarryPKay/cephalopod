#include "ModeratePlayer.h"



ModeratePlayer::ModeratePlayer(Color color, BoardModel * board)
	: Player(color, board)
{
}

ModeratePlayer::~ModeratePlayer()
{
}

Move ModeratePlayer::getMove()
{
	vector<Move> potentialMoves = board->getAllPossibleMoves(color);
	int index = rand() % potentialMoves.size();
	return potentialMoves[index];
}
