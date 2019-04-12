#pragma once
#include "BoardModel.h"
#include "BoardViewer.h"
#include "Player.h"
#include <vector>
#include "GameAnalyzer.h"

/*
 * Mediates most of the interaction between game objects such as players, the board
 * and the board viewer.
 */
class GameController final
{
public:

	/* LIFECYCLE */

	GameController() = default; /* constructor */
	GameController(const GameController&) = delete; /* copy */
	GameController(GameController&&) = delete; /* move */
	~GameController(); /* destructor */

	/* OPERATORS */

	GameController& operator=(const GameController&) = delete; /* copy assignment */
	GameController& operator=(GameController&&) = delete; /* move assignment */

	/* METHODS */

	/*
	 * Runs the program life cycle.
	 */
	void run();

private:

	/* METHODS */

	/*
	 * Runs the entire game life cycle from start to end.
	 */
	void play();

	/*
	 * Calls all init functions to get the game into a playable state.
	 *
	 * Post-condition:
	 * - Data members will point to the appropriate objects.
	 * - The seed for randomness will be set with clock.
	 */
	void init();

	/*
	 * Prompts user for board dimensions and initializes board_ with a pointer
	 * to a board of the given dimensions.
	 *
	 * Pre-condition:
	 * - Dimensions are within a 3 by 3 and 9 by 9 range inclusive.
	 *
	 * Post-condition:
	 * - A playable board.
	 */
	void initBoard();

	/*
	 * Initializes gameAnalyzer_ with board_.
	 *
	 * pre-condition:
	 * - board_ has been initialized.
	 *
	 * Post-condition:
	 * - A initialized gameAnalyzer that can check moves against the game rules.
	 */
	void initGameAnalyzer();

	/*
	 * Initializes boardViewer with board_.
	 *
	 * Pre-condition:
	 * - board_ has been initialized.
	 *
	 * Post-condition:
	 * - A initialized boardViewer that can show the board state to the console.
	 */
	void initBoardView();

	/*
	 * Prompts for player types and Initializes.
	 *
	 * pre-condition:
	 * - A playerColor and playerType that exists within the enums in common.h
	 * - A derived class from Player with a corresponding const in playerType enum.
	 *
	 * Post-condition:
	 * - players_ size will be 2.
	 */
	void initPlayers();

	/*
	 * Initializes the individual player.
	 *
	 * @param playerColor What color will designate this player.
	 * @param playerType What kind of player is this (computer, human?).
	 *
	 * - A playerColor and playerType that exists within the enums in common.h
	 * - A derived class from Player with a corresponding const in playerType enum
	 *
	 * Post-condition:
	 * - players_ size increase by 1.
	 */
	void initPlayer(PlayerColor playerColor, PlayerType playerType);

	/*
	 * Hands control over to each player exactly once.
	 *
	 * Pre-condition:
	 * - GameController components have been initialized.
	 * - board_ is not full.
	 *
	 * Post-condition:
	 * - board_ state will be altered.
	 */
	void cycleTurns();

	/*
	 * Hands control over to a single player so that a move can be acquired and
	 * placed.
	 *
	 * @param player The player to whom control should be given.
	 *
	 * Pre-condition:
	 * - A valid move is acquired from the player.
	 *
	 * Post-condition:
	 * - board_ state will be altered.
	 */
	void delegateTurn(Player* player) const;

	/*
	 * Prompts user for the kind of AI algorithm that should be used by a hard
	 * computer and any associated settings.
	 *
	 * @param algorithmType The desired algorithm to be used.
	 * @param depth The desired depth for which the algorithm will search a tree
	 * for the best move.
	 *
	 * Pre-condition:
	 * - The appropriate AI algorithm functions exist within the HardComputer class
	 * - for the associated AiAlgorithm enum constant.
	 *
	 * Post-condition:
	 * - The params will hold the desired values given by the user.
	 */
	void promptForAiSettings(AiAlgorithm& algorithmType, uint32_t& depth) const;

	/* DATA MEMBERS */

	BoardModel* board_{};
	BoardViewer* boardViewer_{};
	GameAnalyzer* gameAnalyzer_{};
	vector<Player*> players_;
	// Tracks the state of game (I.E on going or ended).
	GameState gameState_ = SETTINGS;
};
