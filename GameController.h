#pragma once
#include <time.h>
#include "BoardModel.h"
#include "BoardViewer.h"
#include "HumanPlayer.h"
#include "EasyComputer.h"

class GameController
{
public:
	GameController();
	~GameController();
	BoardModel* board;
	BoardViewer* boardViewer;
	void run();

private:
	void init();
	void initBoard();
	void initBoardView();
	void initPlayers();
	void play();
	void delegateTurn(Player* player);
	void cycleTurns();
	void displayWinner();
	GameState gameState = settings;
	vector<Player*> players;
};

