#include <iostream>
#include "Board.h"
#include "HumanPLayer.h"

int main()
{
	GameState gameState = settings;
	int rowCount, colCount;
	//TODO: validation
	cout << "Enter board row count\n>";
	cin >> rowCount;
	cout << "Enter board column count\n>";
	cin >> colCount;
	Board board = Board(rowCount, colCount);

	//TODO: implement
	cout << "Enter white player's Type";
	cout << "Enter black player's Type";
	vector<Player*> players;
	players.push_back(new HumanPlayer(white));
	players.push_back(new HumanPlayer(black));

	gameState = GameState::inProgress;

	while (gameState == GameState::inProgress)
	{
		for (Player* player : players) {
			
			board.print();
			while (!board.setMove(player->getMove())) {
				board.print();
				cout << "Invalid move.\n"; 
			};

			if (board.isBoardFull())
			{
				gameState = GameState::end;
				board.print();
				break;
			}
		}
	}

	if (board.getMajorityColor() == black)
	{
		cout << "BLACK WINS\n";
	}
	else if (board.getMajorityColor() == white)
	{
		cout << "WHITE WINS\n";
	}
	else
	{
		cout << "DRAW\n";
	}

	cout << "Enter in any input to exit.\n>";
	char keepOpen;
	std::cin >> keepOpen;
	return 0;
}