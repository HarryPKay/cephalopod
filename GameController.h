#pragma once
#include "BoardModel.h"
#include "BoardViewer.h"
#include "Player.h"
#include <vector>
#include "GameAnalyzer.h"

/*
 * =====================================================================================
 *        Class:  GameController
 *  Description:  
 * =====================================================================================
 */
class GameController final
{
public:
	/* ====================  LIFECYCLE     ======================================= */
	GameController() = default; /* constructor */
	~GameController(); /* destructor */

	/* ====================  SPECIAL       ======================================= */
	GameController(const GameController&) = delete; /* copy */
	GameController(GameController&&) = delete; /* move */

	/* ====================  OPERATORS     ======================================= */
	GameController& operator=(const GameController&) = delete; /* copy assignment */
	GameController& operator=(GameController&&) = delete; /* move assignment */

	/* ====================  METHODS       ======================================= */
	void play();
	void run();
	void cycleTurns();
	void delegateTurn(Player* player) const;
	void displayWinner() const;
	void promptForAiSettings(AiAlgorithm& algorithmType, uint32_t& value) const;
	void init();
	void initBoard();
	void initGameAnalyzer();
	void initBoardView();
	void initPlayers();
	void initPlayer(PlayerColor playerColor, PlayerType playerType);

private:
	/* ====================  DATA MEMBERS  ======================================= */
	BoardModel* board_{};
	BoardViewer* boardViewer_{};
	GameAnalyzer* gameAnalyzer_{};
	vector<Player*> players_;
	GameState gameState_ = SETTINGS;
}; /* -----  end of class GameController  ----- */
