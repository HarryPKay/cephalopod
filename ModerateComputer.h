#pragma once
#include "Player.h"
class ModerateComputer :
	public Player
{
public:
	ModerateComputer(Color color, BoardModel * board);
	virtual ~ModerateComputer();
	Move getMove() override;
};
