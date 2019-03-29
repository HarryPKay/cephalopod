#pragma once
#include <time.h>
#include "BoardModel.h"
#include "BoardViewer.h"
#include "HumanPlayer.h"
#include "EasyComputer.h"
#include "HardComputer.h"

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
	void initPlayer(Color playerColor, PlayerType playerType);
	void play();
	void delegateTurn(Player* player);
	void cycleTurns();
	void displayWinner();
	void promptForAISettings(AIAlgorithm& algorithmType, int& depth);
	GameState gameState = settings;
	vector<Player*> players;
};

