#include "GameController.h"
#include "EasyComputer.h"
#include "HardComputer.h"
#include "Helpers.h"
#include "HumanPlayer.h"
#include "ModerateComputer.h"
#include <cassert>
#include <ctime>
#include <iostream>

GameController::~GameController()
{
	delete boardViewer_;
	delete board_;

	for (auto player : players_)
	{
		delete player;
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  run
 *  Description:  Calls init() to set up a playable game and then calls
 *                play() to run the game cycle.
 * =====================================================================================
 */
void GameController::run()
{
	init();
	play();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init
 *  Description:  Initialize GameController objects in the correct order.
 * =====================================================================================
 */
void GameController::init()
{
	srand(clock());
	initBoard();
	initGameAnalyzer();
	initBoardView();
	initPlayers();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initBoard
 *  Description:  Prompts user for the desired board direction_size and then initializes
 *                the board.
 *          pre:  Dimensions are within a 3 by 3 and 9 by 9 range inclusive.
 * =====================================================================================
 */
void GameController::initBoard()
{
	cout << "\nSelect a board size\n\n";
	cout << "1) 3 by 3\n";
	cout << "2) 3 by 5\n";
	cout << "3) 5 by 5\n";
	cout << "4) custom\n\n> ";

	uint32_t selection = 0;

	promptForInteger(selection);

	switch (--selection)
	{
	case 0:
		board_ = new BoardModel(3, 3);
		break;
	case 1:
		board_ = new BoardModel(3, 5);
		break;
	case 2:
		board_ = new BoardModel(5, 5);
		break;
	case 3:
		uint32_t rowCount, colCount;

		do
		{
			cout << "\nEnter board row and column size e.g: 1 3\n";
			cout << "Valid column range: " << COL_MIN << "-" << COL_MAX << endl;
			cout << "Valid row range: " << ROW_MIN << "-" << ROW_MAX << "\n> ";

			promptForInteger(rowCount, colCount);

			if (rowCount > ROW_MAX || rowCount < ROW_MIN ||
				colCount > COL_MAX || colCount < COL_MIN)
			{
				cout << "Invalid row or column size.\n";
			}
		}
		while (rowCount > ROW_MAX || rowCount < ROW_MIN ||
			colCount > COL_MAX || colCount < COL_MIN);

		board_ = new BoardModel(rowCount, colCount);
		break;

	default:
		cout << "Invalid selection\n\n";
		initBoard();
	}
}

void GameController::initGameAnalyzer()
{
	assert(board_ != nullptr);
	gameAnalyzer_ = new GameAnalyzer(board_);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initBoardView
 *  Description:  Initializes the BoardViewer.
 *          pre:  Board has been initialized.:       
 * =====================================================================================
 */
void GameController::initBoardView()
{
	assert(board_ != nullptr);
	boardViewer_ = new BoardViewer(board_);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initPlayers
 *  Description:  Prompts for the type of each player and initializes those
 *                players.
 *          pre:  Board has been initialized.
 *                Type belongs to PlayerType enum.
 * =====================================================================================
 */
void GameController::initPlayers()
{
	assert(board_ != nullptr);

	for (uint32_t i = 0; i < PLAYER_COUNT; ++i)
	{
		uint32_t selection = 0;

		do
		{
			cout << "\nSelect player type for color: " << playerColorEnumToString(static_cast<PlayerColor>(i)) << endl
				<< endl;

			for (auto j = 0; j < PLAYER_TYPE_SIZE; ++j)
			{
				cout << j + 1 << ") " << playerTypeEnumToString(static_cast<PlayerType>(j)) << "\n";
			}

			promptForInteger(selection);

			--selection;

			if (selection < 0 || selection >= PLAYER_TYPE_SIZE)
			{
				cout << "Invalid selection.\n";
			}
		}
		while (selection < 0 || selection >= PLAYER_TYPE_SIZE);

		initPlayer(static_cast<PlayerColor>(i), static_cast<PlayerType>(selection));
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initPlayer
 *  Description:  Prompts for appropiate settings given the player type and
 *                then initializes the player.
 * =====================================================================================
 */
void GameController::initPlayer(const PlayerColor playerColor, const PlayerType playerType)
{
	uint32_t depth = 0;
	AiAlgorithm algorithmType;

	switch (playerType)
	{
	case HUMAN_PLAYER:
		players_.push_back(new HumanPlayer(playerColor, gameAnalyzer_, board_));
		break;
	case HARD_COMPUTER:
		promptForAiSettings(algorithmType, depth);
		players_.push_back(new HardComputer(playerColor, gameAnalyzer_, board_, algorithmType, depth));
		break;
	case MODERATE_COMPUTER:
		players_.push_back(new ModerateComputer(playerColor, gameAnalyzer_));
		break;
	case EASY_COMPUTER:
		players_.push_back(new EasyComputer(playerColor, gameAnalyzer_));
		break;
	default: ;
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initPlayer
 *  Description:  Runs the game life cycle from start to end.
 *          pre:  All GameController objects have been initialized.
 * =====================================================================================
 */
void GameController::play()
{
	gameState_ = IN_PROGRESS;
	boardViewer_->renderBoardToConsole();
	while (gameState_ == IN_PROGRESS)
	{
		cycleTurns();
	}
	displayWinner();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initPlayer
 *  Description:  Hands control over to the player so that a move can be 
 * =====================================================================================
 */
void GameController::delegateTurn(Player* player) const
{
	auto isMoveValid = false;

	while (!isMoveValid)
	{
		const auto move = player->promptForMove();
		isMoveValid = gameAnalyzer_->isMoveValid(move);

		if (!isMoveValid)
		{
			cout << "Invalid move.\n";
		}
		else
		{
			const auto pipSum = gameAnalyzer_->sumPipForMove(move);
			board_->setMove(move, pipSum);
		}
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cycleTurns
 *  Description:  For each player, hands control over to that player so that
 *                a move can be acquired and placed on the board.
 * =====================================================================================
 */
void GameController::cycleTurns()
{
	for (auto player : players_)
	{
		cout << "\n"
			<< playerColorEnumToString(player->getPlayerColor()) << "'s turn\n";
		delegateTurn(player);
		boardViewer_->renderBoardToConsole();

		if (board_->isBoardFull())
		{
			gameState_ = END;
			break;
		}
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  displayWinner
 *  Description:  Determines who has won based on who owns the majority of the
 *                board, printing out the result.
 * =====================================================================================
 */
void GameController::displayWinner() const
{
	const auto color = gameAnalyzer_->findMajorityColor();

	if (color == BLACK)
	{
		cout << "\nBLACK WINS\n";
	}
	else if (color == WHITE)
	{
		cout << "\nWHITE WINS\n";
	}
	else
	{
		cout << "\nDRAW\n";
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  promptForAISettings
 *  Description:  Prompts for the algorithm to be used for the HardComputer
 *                in determining how it decides where to place it's moves.
 * =====================================================================================
 */
void GameController::promptForAiSettings(AiAlgorithm& algorithmType, uint32_t& depth) const
{
	uint32_t selection = 0;

	do
	{
		for (auto i = 0; i < AI_ALGORITHM_SIZE; ++i)
		{
			cout << i + 1 << ") " << aiAlgorithmEnumToString(static_cast<AiAlgorithm>(i)) << "\n";
		}

		promptForInteger(selection);

		--selection;

		if (selection >= AI_ALGORITHM_SIZE || selection < 0)
		{
			cout << "Invalid selection.\n";
		}
	}
	while (selection >= AI_ALGORITHM_SIZE || selection < 0);

	algorithmType = static_cast<AiAlgorithm>(selection);

	if (algorithmType == MONTECARLO)
	{
		depth = 0;
		return;
	}

	do
	{
		cout << "Enter depth of search\n>";

		promptForInteger(depth);

		if (depth < MIN_DEPTH_SEARCH)
		{
			cout << "Depth must be an integer greater than " << MIN_DEPTH_SEARCH << ".\n";
		}
	}
	while (depth < MIN_DEPTH_SEARCH);
}
