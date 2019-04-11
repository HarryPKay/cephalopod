#pragma once
#include "BoardModel.h"
#include "Move.h"
#include "Common.h"

/*
 * =====================================================================================
 *        Class:  GameAnalyzer
 *  Description:  
 *
 * =====================================================================================
 */
class GameAnalyzer final
{
	typedef vector<Direction> Captures;

public:
	/* ====================  LIFECYCLE     ======================================= */
	GameAnalyzer() = default; /* constructor */
	GameAnalyzer(BoardModel* board);
	~GameAnalyzer() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	GameAnalyzer(const GameAnalyzer&) = delete; /* copy */
	GameAnalyzer(GameAnalyzer&&) = delete; /* move */

	/* ====================  VALIDATORS    ======================================= */
	bool isMoveValid(Move move);
	bool isCaptureValid(Move move);
	bool mustCapture(Move move);

	/* ====================  METHODS       ======================================= */
	uint32_t sumCellsWithColor(PlayerColor color) const;
	uint32_t sumPipForMove(Move move) const;
	PlayerColor findMajorityColor() const;
	vector<Move> findPossibleMoves(PlayerColor playerColor, Position position);
	vector<Move> findAllPossibleMoves(PlayerColor playerColor);
	void printPossibleCaptures(const vector<Move>& moves) const;

	/* ====================  OPERATORS     ======================================= */
	GameAnalyzer& operator=(const GameAnalyzer&) = default; /* copy assignment */
	GameAnalyzer& operator=(GameAnalyzer&&) = default; /* move assignment */

	/* ====================  METHODS       ======================================= */

private:
	/* ====================  METHODS       ======================================= */

	/* ====================  DATA MEMBERS  ======================================= */
	BoardModel* board_{};
	vector<Captures> captureCombinations_;
}; /* -----  end of class GameAnalyzer  ----- */
