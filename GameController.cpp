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
	int selection = 0;
	int rowCount, colCount;

	cout << "\nSelect a board size\n\n";
	cout << "1) 3 by 3\n";
	cout << "2) 3 by 5\n";
	cout << "3) 5 by 5\n";
	cout << "4) custom\n\n> ";
	cin >> selection;

	while (cin.fail()) {
		cout << "Integers accepted only" << std::endl;
		cin.clear();
		cin.ignore(CIN_IGNORE_BUFFER_SIZE, '\n');
		cout << "> ";
		cin >> selection;
	}

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

		do
		{
			cout << "\nEnter board row and column size e.g: 1 3\n";
			cout << "Valid column range: " << COL_MIN << "-" << COL_MAX << endl;
			cout << "Valid row range: " << ROW_MIN << "-" << ROW_MAX << "\n> ";

			cin >> rowCount >> colCount;

			while (cin.fail()) {
				cout << "Integers accepted only" << std::endl;
				cin.clear();
				cin.ignore(CIN_IGNORE_BUFFER_SIZE, '\n');
				cout << "> ";
				cin >> rowCount >> colCount;
			}

			if (rowCount > ROW_MAX || rowCount < ROW_MIN ||
				colCount > COL_MAX || colCount < COL_MIN)
			{
				cout << "Invalid row or column size.\n";
			}

		} while (rowCount > ROW_MAX || rowCount < ROW_MIN ||
			colCount > COL_MAX || colCount < COL_MIN);
		
		board_ = new BoardModel(rowCount, colCount);
		break;

	default:
		cout << "Invalid selection\n\n";
		initBoard();
	}
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
	
	for (auto i = 0; i < PLAYER_COUNT; ++i)
	{
		auto selection = 0;

		do
		{
			cout << "\nSelect player type for color: " << colorEnumToString(static_cast<Color>(i)) << endl
				<< endl;

			for (auto j = 0; j < player_type_size; ++j)
			{
				cout << j + 1 << ") " << playerTypeEnumToString(static_cast<PlayerType>(j)) << "\n";
			}

			cin >> selection;

			while (cin.fail()) {
				cout << "Integers accepted only." << std::endl;
				cin.clear();
				cin.ignore(CIN_IGNORE_BUFFER_SIZE, '\n');
				cout << "> ";
				cin >> selection;
			}

			--selection;

			if (selection < 0 || selection >= player_type_size)
			{
				cout << "Invalid selection.\n";
			}

		} while (selection < 0 || selection >= player_type_size);
		
		initPlayer(static_cast<Color>(i), static_cast<PlayerType>(selection));
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initPlayer
 *  Description:  Prompts for appropiate settings given the player type and
 *                then initializes the player.
 * =====================================================================================
 */
void GameController::initPlayer(const Color playerColor, const PlayerType playerType)
{
	auto depth = 0;
	AiAlgorithm algorithmType;

	switch (playerType)
	{
	case human_player:
		players_.push_back(new HumanPlayer(playerColor, board_));
		break;
	case hard_computer:
		promptForAiSettings(algorithmType, depth);
		players_.push_back(new HardComputer(playerColor, board_, algorithmType, depth));
		break;
	case moderate_computer:
		players_.push_back(new ModerateComputer(playerColor, board_));
		break;
	case easy_computer:
		players_.push_back(new EasyComputer(playerColor, board_));
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
	gameState_ = in_progress;
	boardViewer_->renderBoardToConsole();
	while (gameState_ == in_progress)
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
	while (!board_->setMove(player->promptForMove()))
	{
		boardViewer_->renderBoardToConsole();
		cout << "Invalid move.\n";
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
			<< colorEnumToString(player->getColor()) << "'s turn\n";
		delegateTurn(player);
		boardViewer_->renderBoardToConsole();

		if (board_->isBoardFull())
		{
			gameState_ = GameState::end;
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
	if (board_->findMajorityColor() == black)
	{
		cout << "\nBLACK WINS\n";
	}
	else if (board_->findMajorityColor() == white)
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
void GameController::promptForAiSettings(AiAlgorithm& algorithmType, int& depth) const
{
	auto selection = 0;

	do
	{
		for (auto i = 0; i < ai_algorithm_size; ++i)
		{
			cout << i + 1 << ") " << aiAlgorithmEnumToString(static_cast<AiAlgorithm>(i)) << "\n";
		}
		
		cin >> selection;

		while (cin.fail()) {
			cout << "Integers accepted only" << std::endl;
			cin.clear();
			cin.ignore(CIN_IGNORE_BUFFER_SIZE, '\n');
			cout << "> ";
			cin >> selection;
		}

		--selection;
		if (selection >= ai_algorithm_size || selection < 0)
		{
			cout << "Invalid selection.\n";
		}

	} while (selection >= ai_algorithm_size || selection < 0);

	algorithmType = static_cast<AiAlgorithm>(selection);

	do
	{
		cout << "Enter depth of search\n>";
		cin >> depth;

		while (cin.fail()) {
			cout << "Integers accepted only" << std::endl;
			cin.clear();
			cin.ignore(CIN_IGNORE_BUFFER_SIZE, '\n');
			cout << "> ";
			cin >> selection;
		}

		if (depth < 1)
		{
			cout << "Depth must be an integer greater than 0.\n";
		}

	} while (depth < 1);
}
