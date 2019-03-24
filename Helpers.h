#pragma once
#include <algorithm>
#include <iostream>
#include "Common.h"

namespace cephalopod
{
	using namespace std;
	string directionEnumToString(Direction direction);

	template<typename T>
	vector<vector<T>> generateCombinations(const vector<T> & source, int combinationSize)
	{
		vector<T> combination;
		vector<vector<T>> combinations;
		string bitmask(combinationSize, 1);
		bitmask.resize(source.size(), 0);

		do
		{
			for (int i = 0; i < source.size(); ++i)
			{
				if (bitmask[i] == 1) {
					combination.push_back(source[i]);
				}
			}
			combinations.push_back(combination);
			combination.clear();

		} while (prev_permutation(bitmask.begin(), bitmask.end()));

		return combinations;
	}

	template<typename T>
	vector<vector<T>> generateCombinationsVaryingSize(const vector<T> & source, int minSize, int maxSize)
	{
		vector<vector<T>> combinations;
		for (int i = minSize; i <= maxSize; ++i)
		{
			vector<vector<Direction>> temp = generateCombinations(source, i);
			combinations.insert(std::end(combinations), std::begin(temp), std::end(temp));
		}
		return combinations;
	}
}


