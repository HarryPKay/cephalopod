#include "GameController.h"



GameController::GameController()
{
}

GameController::~GameController()
{
	delete boardViewer;
	delete board;

	for (Player* player : players) 
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
	srand(time(0));
	initBoard();
	initBoardView();
	initPlayers();
}

void GameController::initBoard()
{
	// TODO: validation
	int selection = 0;
	int rowCount, colCount;

	cout << "Select a board size\n\n";
	cout << "1) 3 by 3\n";
	cout << "2) 3 by 5\n";
	cout << "3) 5 by 5\n";
	cout << "4) custom\n>";
	cin >> selection;

	switch (--selection)
	{
	case 0:
		board = new BoardModel(3,3);
		break;
	case 1:
		board = new BoardModel(3,5);
		break;
	case 2:
		board = new BoardModel(5,5);
		break;
	case 3:
		cout << "Enter board row count\n>";
		cin >> rowCount;
		cout << "Enter board column count\n\n>";
		cin >> colCount;
		board = new BoardModel(rowCount, colCount);
	default:
		cout << "Invalid selection\n\n";
		initPlayers();
	}
}

void GameController::initBoardView()
{
	boardViewer = new BoardViewer(board);
}

void GameController::initPlayers()
{
	// TODO: validation
	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		int selection = 0;
		cout << "Select player type for color: " << colorEnumToString((Color)i) << endl << endl;
		cout << "1) Human Player\n";
		cout << "2) Easy Computer\n";
		cout << "3) Hard Computer\n>";
		cin >> selection;
		initPlayer((Color)i, (PlayerType)--selection);
	}
}

void GameController::initPlayer(Color playerColor, PlayerType playerType)
{
	int depth = 0;
	AIAlgorithm algorithmType;

	switch (playerType)
	{
	case human:
		players.push_back(new HumanPlayer(playerColor));
		break;
	case hardComputer:
		promptForAISettings(algorithmType, depth);
		players.push_back(new HardComputer(playerColor, board, algorithmType, depth));
		break;
	case easyComputer:
		players.push_back(new EasyComputer(playerColor, board));
		break;
	}
}

void GameController::play()
{
	gameState = inProgress;
	boardViewer->renderBoardToConsole();
	while (gameState == GameState::inProgress)
	{
		cycleTurns();
	}
	displayWinner();
}

void GameController::delegateTurn(Player * player)
{
	while (!board->setMove(player->getMove())) 
	{
		boardViewer->renderBoardToConsole();
		cout << "Invalid move.\n";
	};
}

void GameController::cycleTurns()
{
	for (Player* player : players) {

		delegateTurn(player);
		boardViewer->renderBoardToConsole();

		if (board->isBoardFull())
		{
			gameState = GameState::end;
			break;
		}
	}
}

void GameController::displayWinner()
{
	if (board->getMajorityColor() == black)
	{
		cout << "BLACK WINS\n";
	}
	else if (board->getMajorityColor() == white)
	{
		cout << "WHITE WINS\n";
	}
	else
	{
		cout << "DRAW\n";
	}
}

void GameController::promptForAISettings(AIAlgorithm & algorithmType, int & depth)
{
	cout << "Select algorithm:\n\n";
	cout << "1) alphabeta\n";
	cout << "2) minimax\n\n>";
	int selection;
	cin >> selection;

	if (selection > 2)
	{
		cout << "Invalid selection\n\n";
		promptForAISettings(algorithmType, depth);
	}

	algorithmType = (AIAlgorithm)--selection;

	cout << "Enter depth of search\n>";
	cin >> depth;
}
