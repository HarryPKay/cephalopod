#pragma once
#include "Common.h"
#include "Player.h"
#include "GameAnalyzer.h"

using namespace std;
using namespace cephalopod;

/*
 * Player that uses tree search AI algorithms to determine where to move.
 */
class HardComputer final : public Player
{
public:
	/* LIFECYCLE */
	HardComputer() = delete; /* constructor */
	HardComputer(
		PlayerColor playerColor,
		GameAnalyzer* gameAnalyzer,
		BoardModel* boardModel,
		AiAlgorithm algorithmType,
		uint32_t depth
	);
	HardComputer(const HardComputer&) = delete; /* copy */
	HardComputer(HardComputer&&) = delete; /* move */
	~HardComputer() = default; /* destructor */

	/* OPERATORS */
	HardComputer& operator=(const HardComputer&) = delete; /* copy assignment */
	HardComputer& operator=(HardComputer&&) = delete; /* move assignment */

private:
	/* METHODS */

	/*
	 * Retrieve a move from this player.
	 * 
	 * @return A valid move.
	 * 
	 * Pre-condition:
	 * - The board is not full.
	 */
	Move promptForMove() override;

	/*
	 * For every possible move for the current board state, find the move that has
	 * the highest evaluation from evaluate(). Has similar implementation to 
	 * maxValue(), however, it also has book keeping to record which move had the 
	 * highest evaluation.
	 * 
	 * Computational complexity analysis:
	 * 
	 *		Let moves.size() = n
	 *		Let depth_ = m
	 *		Complexity: O(n^m)
	 *		
	 * Explanation:
	 * minimax() calls minValue which is indirectly recursive with maxValue()
	 * for a total of m times. For each of these calls, moves are evaluated for
	 * a total of n times. For example, if we assume that n = 3, and m = 2, then
	 * we have three moves for every level of depth, for a total of 6 moves that
	 * need to be processed:
	 * 
	 * m_0: n_0, n_1, n_2
	 * m_1: n_0, n_1, n_2
	 * 
	 * which is 3^2 = 6, or n^m
	 * Therefor, the time complexity is O(n^m)
	 *  
	 * Pre-condition:
	 * - The board is not full.
	 * 
	 * Post-condition:
	 * - The board is left unchanged from simulations.
	 * 
	 * @return A valid move.
	 */
	Move minimax();

	/*
	 * For every child board states for all of the current possible moves, return
	 * the value that maximizes the evaluation given by evaluate().
	 * 
	 * Base case:
	 * - The child board state is terminal (full)
	 * - The desired depth in the search
	 * 
	 * @param depth The depth of the tree of possible board states to search.
	 * @return The evaluation given by evaluate().
	 */
	float_t minValue(uint32_t depth);

	/*
	 * For every child board states for all of the current possible moves, return
	 * the value that maximizes the evaluation given by evaluate().
	 *
	 * Base case:
	 * - The child board state is terminal (full)
	 * - The desired depth in the search
	 *
	 * @param depth The depth of the tree of possible board states to search.
	 * @return The evaluation given by evaluate().
	 */
	float_t maxValue(uint32_t depth);

	/*
	 * Same as minimax(), however, prunes child board states that would not
	 * influence the final decision for which move to return.
	 * 
	 * Pre-condition:
	 * - The board is not full.
	 *
	 * Post-condition:
	 * - The board is left unchanged from simulations.
	 *
	 * @return A valid move.
	 */
	Move alphaBeta();

	/*
	 * For every child board states for all of the current possible moves, return
	 * the value that maximizes the evaluation given by evaluate(). The function will
	 * assign beta an evaluation less than it for every child evaluation.
	 * 
	 * Base case:
	 * - The child board state is terminal (full)
	 * - The desired depth in the search
	 * - Alpha is less than or equal to a child node evaluation.
	 *
	 * @param depth The depth of the tree of possible board states to search.
	 * @param alpha The greatest evaluation found so far.
	 * @param beta The lowest evaluation found so far.
	 * @return The evaluation given by evaluate().
	 */
	float_t minValue(uint32_t depth, float_t alpha, float_t beta);

	/*
	 * For every child board states for all of the current possible moves, return
	 * the value that maximizes the evaluation given by evaluate(). The function will
	 * assign alpha an evaluation greater than it for every child evaluation.
	 *
	 * Base case:
	 * - The child board state is terminal (full)
	 * - The desired depth in the search
	 * - A child evaluation is equal to or greater than Beta.
	 *
	 * @param depth The depth of the tree of possible board states to search.
	 * @param alpha The greatest evaluation found so far.
	 * @param beta The lowest evaluation found so far.
	 * @return The evaluation given by evaluate().
	 */
	float_t maxValue(uint32_t depth, float_t alpha, float_t beta);

	/*
	 * Finds the best move simulating random games for each move possible move.
	 *
	 * @return The move that had the highest win:simCount ratio.
	 *
	 * Pre-condition:
	 * - The board is not full.
	 *
	 * Post-condition:
	 * - The board state remains unchanged.
	 */
	Move monteCarlo() const;

	/*
	 * Begins a new simulation for the current board state, returning the
	 * ratio of wins, given the total simulation count.
	 */
	float_t simulation() const;

	/*
	 * Plays out a simulation, moving randomly until board is full.
	 * 
	 * @param moveCount the number of random moves that have been played.
	 * Used to backtrack the board state back to it's original state.
	 * @param color The player's color whose turn it is for the current 
	 * board simulation state.
	 * @return -1 If the game was a loss for playerColor_, 0 for a draw
	 * a 1 for a win.
	 */
	float_t expansion(uint32_t moveCount, PlayerColor color) const;

	/*
	 * Finds the heuristic for the current board state. That is, the value that
	 * maximum cells occupied by this player and the minimum occupied by the 
	 * opponent.
	 */
	float_t evaluate() const;

	/* DATA MEMBERS */
	BoardModel* board_{};
	AiAlgorithm algorithmType_;
	uint32_t depth_;
};
