#pragma once
#include "BoardModel.h"
#include "Move.h"
#include "Common.h"

/*
 * Provides the necessary methods to ensure that a player move plays by the rules.
 */
class GameAnalyzer final
{
	/* TYPEDEFS */

	typedef vector<Direction> Captures;

public:

	/* LIFECYCLE */

	GameAnalyzer() = default; /* constructor */
	GameAnalyzer(BoardModel* board);
	GameAnalyzer(const GameAnalyzer&) = delete; /* copy */
	GameAnalyzer(GameAnalyzer&&) = delete; /* move */
	~GameAnalyzer() = default; /* destructor */

	/* OPERATORS */

	GameAnalyzer& operator=(const GameAnalyzer&) = default; /* copy assignment */
	GameAnalyzer& operator=(GameAnalyzer&&) = default; /* move assignment */

	/* VALIDATORS */

	/*
	 * Checks that the move will follows the game rules.
	 * 
	 * @param move The move to check
	 * @return The boolean value indicating if the move does follow the rules.
	 */
	bool isMoveValid(Move move);

	/*
	 * Checks that the move will follows the capture rules.
	 * 
	 * @param move The move to check
	 * @return The boolean value indicating if the move does capture the rules.
	 */
	bool isCaptureValid(Move move);

	/*
	 * Checks whether the move must be a capture.
	 *
     * @param move The move to check
	 * @return The boolean value indicating if the move must capture.
	 */
	bool mustCapture(Move move);

	/* METHODS */
	/*
	 * Count how many cells belong to a given color
	 * 
	 * @param color The desired color for which to count.
	 * @return The count of cells who are owned by that color.
	 */
	uint32_t countCellsWithColor(PlayerColor color) const;

	/*
	 * For a move's capture, sums the pip of the targeted capturing cells.
	 * 
	 * @param move The move for which a capture belongs.
	 * @return A one if there is no captures, or, the pip sum of the captures.
	 */
	uint32_t sumPipForMove(Move move) const;

	/*
	 * Finds the color who occupies most of the cells.
	 * 
	 * @return The color who occupies the most.
	 */
	PlayerColor findMajorityColor() const;

	/*
	* Finds who has won based on who occupies the majority of the cells.
	* 
	* Pre-condition:
	* - The board is full.
	*/
	PlayerColor findWinnersColor() const;

	/*
	 * Finds all of the available captures for a position that could be played 
	 * on the current turn.
	 * 
	 * @param playerColor The owner of the moves.
	 * @param position The position for which captures should be found for.
	 * @return The vector of moves found.
	 */
	vector<Move> findValidMoves(PlayerColor playerColor, Position position);

	/*
	 * Find all of the available positions and corresponding captures that could
	 * be played on the current turn.
	 * 
	 * @param playerColor The owner of the moves.
	 * @return The vector of moves found.
	 */
	vector<Move> findAllValidMoves(PlayerColor playerColor);

	/*
	 * Prints to console all of the possible captures available to the user for
	 * a given position.
	 * 
	 * Pre-condition:
	 * - There are captures to print.
	 * - All moves have the same position as each other.
	 * 
	 * @param moves The vector holding all of the possible captures for a given
	 * position
	 */
	void printValidCaptures(const vector<Move>& moves) const;

	/*
	* Prints out the color of the player who owns the majority of the cells and
	* therefore is the winner
	* 
	* Pre-condition:
	* - The board is full, and therefore, a winner can be displayed.
	*/
	void displayWinner() const;

private:

	/* DATA MEMBERS */

	BoardModel* board_{};

	// Used as a guide to ensure that all possible captures are generated.
	vector<Captures> captureCombinations_;
};
