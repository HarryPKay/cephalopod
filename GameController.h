#pragma once
#include <assert.h>
#include <time.h>
#include "BoardModel.h"
#include "BoardViewer.h"
#include "HumanPlayer.h"
#include "EasyComputer.h"
#include "HardComputer.h"


/*
 * =====================================================================================
 *        Class:  GameController
 *  Description:  
 * =====================================================================================
 */
class GameController
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        GameController ();                             /* constructor */
		~GameController ();							   /* destructor */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

        /* ====================  METHODS       ======================================= */
        void run();

        /* ====================  DATA MEMBERS  ======================================= */

    private:
        /* ====================  METHODS       ======================================= */
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

        /* ====================  DATA MEMBERS  ======================================= */
		BoardModel* board;
		BoardViewer* boardViewer;
		GameState gameState = settings;
		vector<Player*> players;

}; /* -----  end of class GameController  ----- */


