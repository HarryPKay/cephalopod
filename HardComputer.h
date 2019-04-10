#pragma once
#include "Common.h"
#include "Player.h"

using namespace std;
using namespace cephalopod;

/*
 * =====================================================================================
 *        Class:  HardComputer
 *  Description:  
 *
 * =====================================================================================
 */
class HardComputer final : public Player
{
public:
	/* ====================  LIFECYCLE     ======================================= */
	HardComputer() = delete; /* constructor */
	HardComputer(
		Color color,
		BoardModel* board,
		AiAlgorithm algorithmType,
		int depth);
	~HardComputer() = default; /* destructor */

	/* ====================  SPECIAL       ======================================= */
	HardComputer(const HardComputer&) = delete; /* copy */
	HardComputer(HardComputer&&) = delete; /* move */

	/* ====================  OPERATORS     ======================================= */
	HardComputer& operator=(const HardComputer&) = delete; /* copy assignment */
	HardComputer& operator=(HardComputer&&) = delete; /* move assignment */

private:
	/* ====================  METHODS       ======================================= */
	Move promptForMove() override;
	Move minimax();
	Move alphaBeta();
	float minValue(int depth);
	float maxValue(int depth);
	float minValue(int depth, float alpha, float beta);
	float maxValue(int depth, float alpha, float beta);
	float evaluate() const;

	/* ====================  DATA MEMBERS  ======================================= */
	AiAlgorithm algorithmType_;
	int depth_;
}; /* -----  end of class HardComputer  ----- */
