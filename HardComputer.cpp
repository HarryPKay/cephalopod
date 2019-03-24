#include "HardComputer.h"



HardComputer::HardComputer(Color color, BoardModel * board)
	: Player(color), board(board)
{
	boardViewer = new BoardViewer(board);
}

HardComputer::~HardComputer()
{
}

Move HardComputer::getMove()
{
	//vector<Move> potentialMoves = generatePossibleMoves(board, color);
	Move move = { Position(0, 0), color, vector<Direction>() };
	BestMove bestMove = minimax(board, 3, color, move);
	cout << "bestMove: " << bestMove.move.position.row << bestMove.move.position.col << "\n";
	return bestMove.move;
	//return move;
	//return Move{ Position(0,0),color,vector<Direction>() };
}

BestMove HardComputer::minimax(BoardModel * board, int depth, Color playerColor, const Move & prevMove)
{
	Color opposition = findOpposition(playerColor);
	BestMove bestMove = { {Position(0, 0), playerColor, vector<Direction>() }, 0 };

	if (playerColor == color)
	{
		bestMove.score = INFINITY;
	}
	else
	{
		bestMove.score = -INFINITY;
	}

	if (depth == 0 || board->isBoardFull())
	{
		bestMove.score = evaluate(board);
		return bestMove;
	}

	vector<Move> moves = generatePossibleMoves(board, playerColor);

	for (Move move : moves)
	{
		int score = 0;

		board->setMove(move);
		//cout << "\n\nsimulation set: " << move.position.row << " " << move.position.col << "\n";
		//boardViewer->renderBoardToConsole();
		score = minimax(board, depth - 1, opposition, move).score;
		board->undoMove();
		//cout << "\n\nsimulation delete:\n";
		//boardViewer->renderBoardToConsole();
		if (playerColor == color && score < bestMove.score)
		{
			bestMove.score = score;
			bestMove.move = move;
			
			if (score >= 2)
			{
				cout << "aplayer: " << playerColor << " score: " << score << endl;
				cout << move.position.row << " " << move.position.col << endl;
				char keepOpen;
				cin >> keepOpen;
			}
			
		}
		else if (playerColor != color && score > bestMove.score)
		{
			bestMove.score = score;
			bestMove.move = move;
			
			if (score <= -2)
			{
				cout << "bplayer: " << playerColor << " score: " << score << endl;
				cout << move.position.row << " " << move.position.col << endl;
				char keepOpen;
				cin >> keepOpen;
			}

		}	
	}

	return bestMove;


	//Color opposition = findOpposition(playerColor);

	//BestMove bestMove = { prevMove, evaluate(board) };

	//if (depth == 0 || board->isBoardFull())
	//{
	//	return bestMove;
	//}

	//vector<Move> moves = generatePossibleMoves(board, playerColor);

	//if (playerColor == color)
	//{
	//	float maxScore = -INFINITY;

	//	for (Move move : moves) 
	//	{
	//		board->setMove(move);
	//		bestMove = minimax(board, depth - 1, opposition, move);
	//		bestMove.score = max(maxScore, (float)bestMove.score);
	//		board->undoMove();
	//	}
	//}
	//else
	//{
	//	float minScore = INFINITY;

	//	for (Move move : moves)
	//	{
	//		board->setMove(move);
	//		bestMove = minimax(board, depth - 1, opposition, move);
	//		bestMove.score = min(minScore, (float)bestMove.score);
	//		board->undoMove();
	//	}
	//}

	//return bestMove;
}

int HardComputer::evaluate(BoardModel * board)
{
	int whiteCount = board->getTotalColorCount(white);
	int blackCount = board->getTotalColorCount(black);

	if (color == white)
	{
		return white - black;
	}
	else
	{
		return black - white;
	}
	return 0;
}
