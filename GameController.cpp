#include "GameController.h"

GameController::GameController()
{
}

GameController::~GameController()
{
    delete boardViewer;
    delete board;

    for (Player* player : players) {
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
    srand(time(0));
    initBoard();
    initBoardView();
    initPlayers();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initBoard
 *  Description:  Prompts user for the desired board size and then initializes
 *                the board.
 *          pre:  Dimensions are within a 3 by 3 and 9 by 9 range inclusive.
 * =====================================================================================
 */
void GameController::initBoard()
{
    // TOOD validation
    int selection = 0;
    int rowCount, colCount;

    cout << "Select a board size\n\n";
    cout << "1) 3 by 3\n";
    cout << "2) 3 by 5\n";
    cout << "3) 5 by 5\n";
    cout << "4) custom\n\n> ";
    cin >> selection;

    switch (--selection) {
    case 0:
        board = new BoardModel(3, 3);
        break;
    case 1:
        board = new BoardModel(3, 5);
        break;
    case 2:
        board = new BoardModel(5, 5);
        break;
    case 3:
        cout << "Enter board row and col count e.g: 1 3\n> ";
        cin >> rowCount >> colCount;
        // TOOD validation
        board = new BoardModel(rowCount, colCount);
    default:
        cout << "Invalid selection\n\n";
        initPlayers();
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
	assert(board != nullptr);
    boardViewer = new BoardViewer(board);
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
    assert(board != nullptr);
    //TODO: validation
    for (int i = 0; i < PLAYER_COUNT; ++i) {
        int selection = 0;
        cout << "Select player type for color: " << colorEnumToString((Color)i) << endl
             << endl;
        cout << "1) Human Player\n";
        cout << "2) Easy Computer\n";
        cout << "3) Hard Computer\n\n> ";
        cin >> selection;
        initPlayer((Color)i, (PlayerType)--selection);
    }
	//initPlayer(white, hardComputer);
	//initPlayer(black, easyComputer);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initPlayer
 *  Description:  Prompts for appropiate settings given the player type and
 *                then initializes the player.
 * =====================================================================================
 */
void GameController::initPlayer(Color playerColor, PlayerType playerType)
{
    int depth = 0;
    AIAlgorithm algorithmType;

    switch (playerType) {
    case human:
        players.push_back(new HumanPlayer(playerColor, board));
        break;
    case hardComputer:
        promptForAISettings(algorithmType, depth);
        players.push_back(new HardComputer(playerColor, board, algorithmType, depth));
        //players.push_back(new HardComputer(playerColor, board, alphabeta, 3));
        break;
    case easyComputer:
        players.push_back(new EasyComputer(playerColor, board));
        break;
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
    gameState = inProgress;
    boardViewer->renderBoardToConsole();
    while (gameState == GameState::inProgress) {
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
void GameController::delegateTurn(Player* player)
{
    while (!board->setMove(player->getMove())) {
        boardViewer->renderBoardToConsole();
        cout << "Invalid move.\n";
    };
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
    for (Player* player : players) {
        cout << "\n"
             << colorEnumToString(player->getColor()) << "'s turn\n";
        delegateTurn(player);
        boardViewer->renderBoardToConsole();

        if (board->isBoardFull()) {
            gameState = GameState::end;
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
void GameController::displayWinner()
{
    if (board->getMajorityColor() == black) {
        cout << "\nBLACK WINS\n";
    } else if (board->getMajorityColor() == white) {
        cout << "\nWHITE WINS\n";
    } else {
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
void GameController::promptForAISettings(AIAlgorithm& algorithmType, int& depth)
{
    cout << "Select algorithm:\n\n";
    cout << "1) minimax\n";
    cout << "2) alphabeta\n\n> ";
    int selection;
    cin >> selection;

    if (selection > 2 || selection < 1) {
        cout << "Invalid selection\n\n";
        promptForAISettings(algorithmType, depth);
    }

    algorithmType = (AIAlgorithm)--selection;

    cout << "Enter depth of search\n>";
    cin >> depth;
}
