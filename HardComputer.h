#pragma once
#include "Common.h"
#include "Player.h"
#include "GameAnalyzer.h"

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
		PlayerColor playerColor,
		GameAnalyzer* gameAnalyzer,
		BoardModel* boardModel,
		AiAlgorithm algorithmType,
		uint32_t depth
	);
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
	float_t minValue(uint32_t depth);
	float_t maxValue(uint32_t depth);

	Move alphaBeta();
	float_t minValue(uint32_t depth, float_t alpha, float_t beta);
	float_t maxValue(uint32_t depth, float_t alpha, float_t beta);

	Move monteCarlo() const;
	float_t simulation() const;
	float_t expansion(uint32_t moveCount, PlayerColor color) const;

	float_t evaluate() const;

	/* ====================  DATA MEMBERS  ======================================= */
	BoardModel* board_{};
	AiAlgorithm algorithmType_;
	uint32_t depth_;
}; /* -----  end of class HardComputer  ----- */
