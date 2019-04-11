#pragma once
#include "Common.h"
#include <algorithm>
#include <vector>

namespace cephalopod
{
	using namespace std;

	typedef vector<Direction> Captures;

	string directionEnumToString(Direction direction);
	string playerColorEnumToString(PlayerColor playerColor);
	string playerTypeEnumToString(PlayerType playerType);
	string aiAlgorithmEnumToString(AiAlgorithm aiAlgorithm);
	PlayerColor findOpposition(PlayerColor playerColor);
	void promptForInteger(uint32_t& value);
	void promptForInteger(uint32_t& valueA, uint32_t& valueB);

	template <typename T>
	vector<vector<T>> getCombinationsOfSizeN(const vector<T>& source, uint32_t n)
	{
		vector<T> combination;
		vector<vector<T>> combinations;
		string bitmask(n, 1);
		bitmask.resize(source.size(), 0);

		do
		{
			for (auto i = 0; i < source.size(); ++i)
			{
				if (bitmask[i] == 1)
				{
					combination.push_back(source[i]);
				}
			}
			combinations.push_back(combination);
			combination.clear();
		}
		while (prev_permutation(bitmask.begin(), bitmask.end()));

		return combinations;
	}

	template <typename T>
	vector<vector<T>> getCombinationsOfSizeKtoN(const vector<T>& source, const uint32_t k, const uint32_t n)
	{
		vector<vector<T>> combinations;
		for (auto i = k; i <= n; ++i)
		{
			vector<Captures> temp = getCombinationsOfSizeN(source, i);
			combinations.insert(std::end(combinations), std::begin(temp), std::end(temp));
		}
		return combinations;
	}
}
