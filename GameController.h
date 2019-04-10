#pragma once
#include <vector>
#include "BoardModel.h"
#include "BoardViewer.h"
#include "Player.h"

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
		GameController() = default;                             /* constructor */
		~GameController();										/* destructor */

		/* ====================  SPECIAL       ======================================= */
		GameController(const GameController&) = delete;              /* copy */
		GameController(GameController&&) = delete;                   /* move */

		/* ====================  OPERATORS     ======================================= */
		GameController& operator=(const GameController&) = delete;   /* copy assignment */
		GameController& operator=(GameController&&) = delete;        /* move assignment */

        /* ====================  METHODS       ======================================= */
		void play();
        void run();
		void cycleTurns();
		void delegateTurn(Player* player) const;
		void displayWinner() const;
		void promptForAiSettings(AIAlgorithm& algorithmType, int& depth) const;
		void init();
		void initBoard();
		void initBoardView();
		void initPlayers();
		void initPlayer(Color playerColor, PlayerType playerType);

    private:
        /* ====================  DATA MEMBERS  ======================================= */
		BoardModel* board_{};
		BoardViewer* boardViewer_{};
		GameState gameState_ = settings;
		vector<Player*> players_;

}; /* -----  end of class GameController  ----- */


