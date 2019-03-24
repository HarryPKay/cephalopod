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
	//TODO: validation
	int rowCount, colCount;
	cout << "Enter board row count\n>";
	cin >> rowCount;
	cout << "Enter board column count\n>";
	cin >> colCount;

	board = new BoardModel(rowCount, colCount, generateCombinationsVaryingSize(directions, 2, 4));
}

void GameController::initBoardView()
{
	boardViewer = new BoardViewer(board);
}

void GameController::initPlayers()
{
	//TODO: implement
	cout << "Enter white player's Type\n>";
	cout << "Enter black player's Type\n>";
	cout << "row in initplayers: " << board->getRowCount() << endl;
	//players.push_back(new HumanPlayer(white));
	//players.push_back(new HumanPlayer(black));
	//players.push_back(new EasyComputer(white, board));
	
	
	players.push_back(new HardComputer(white, board));
	players.push_back(new HardComputer(black, board));
	//players.push_back(new EasyComputer(black, board));
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

		//char keepOpen = ' ';
		//do
		//{

		//	cout << "rewind?\n";
		//	cin >> keepOpen;
		//	if (keepOpen == 'y')
		//	{
		//		board->undoMove();
		//		boardViewer->renderBoardToConsole();
		//	}

		//} while (keepOpen == 'y');

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
