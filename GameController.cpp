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
	delete gameAnalyzer_;
	delete boardViewer_;
	delete board_;

	for (auto player : players_)
	{
		delete player;
	}
}

void GameController::run()
{
	init();
	play();
}

void GameController::init()
{
	srand(clock());
	initBoard();
	initGameAnalyzer();
	initBoardView();
	initPlayers();
}

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
			cout << "\nEnter board row and column size (must be odd). e.g: 1 3\n";
			cout << "Valid column range: " << COL_MIN << "-" << COL_MAX << endl;
			cout << "Valid row range: " << ROW_MIN << "-" << ROW_MAX << "\n> ";

			promptForInteger(rowCount, colCount);

			// Are the inputs within the allowable range for board dimensions.
			if (rowCount > ROW_MAX || rowCount < ROW_MIN ||
				colCount > COL_MAX || colCount < COL_MIN ||
				rowCount % 2 == 0 || colCount % 2 == 0)
			{
				cout << "Invalid row or column size.\n";
			}
		}
		while (rowCount > ROW_MAX || rowCount < ROW_MIN ||
			colCount > COL_MAX || colCount < COL_MIN ||
			rowCount % 2 == 0 || colCount % 2 == 0);

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

void GameController::initBoardView()
{
	assert(board_ != nullptr);
	boardViewer_ = new BoardViewer(board_);
}

void GameController::initPlayers()
{
	assert(board_ != nullptr);

	// For each player, prompt for the playerType and initialize it.
	for (uint32_t i = 0; i < PLAYER_COUNT; ++i)
	{
		uint32_t selection = 0;

		do
		{
			cout << "\nSelect player type for color: "
				<< playerColorEnumToString(static_cast<PlayerColor>(i)) << endl << endl;

			// Print out all of the available player types.
			for (auto j = 0; j < PLAYER_TYPE_SIZE; ++j)
			{
				cout << j + 1 << ") "
					<< playerTypeEnumToString(static_cast<PlayerType>(j)) << "\n";
			}

			promptForInteger(selection);

			--selection;

			if (selection < 0 || selection >= PLAYER_TYPE_SIZE)
			{
				cout << "Invalid selection.\n";
			}
		}
		while (selection < 0 || selection >= PLAYER_TYPE_SIZE);

		// Initialize the chosen type.
		initPlayer(static_cast<PlayerColor>(i), static_cast<PlayerType>(selection));
	}
}

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

void GameController::play()
{
	gameState_ = IN_PROGRESS;
	boardViewer_->renderBoardToConsole();

	// While the game is still in progress, continue delegating control via
	// cycleTurns();
	while (gameState_ == IN_PROGRESS)
	{
		cycleTurns();
	}
	gameAnalyzer_->displayWinner();
}

void GameController::delegateTurn(Player* player) const
{
	auto isMoveValid = false;

	// While an invalid move is given, acquire more.
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

void GameController::cycleTurns()
{
	// Give control to each existing player.
	for (auto player : players_)
	{
		cout << "\n" << playerColorEnumToString(player->getPlayerColor()) << "'s turn\n";
		delegateTurn(player);
		boardViewer_->renderBoardToConsole();

		if (board_->isBoardFull())
		{
			gameState_ = END;
			break;
		}
	}
}

void GameController::promptForAiSettings(AiAlgorithm& algorithmType, uint32_t& depth) const
{
	cout << "Select an AI algorithm for the computer to use\n\n";

	uint32_t selection = 0;

	// Prompt user for an AI algorithm.
	do
	{
		// Print the available AI algorithms.
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

	// No need to ask for depth as montecarlo does not use it.
	if (algorithmType == MONTECARLO)
	{
		depth = 0;
		return;
	}

	// Ask for the depth for algorithms such as minimax.
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
