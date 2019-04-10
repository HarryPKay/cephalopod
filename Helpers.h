#pragma once
#include <algorithm>
#include <vector>
#include "Common.h"

namespace cephalopod
{
	typedef vector<Direction> Captures;

	using namespace std;
	string directionEnumToString(Direction direction);
	string colorEnumToString(Color color);
	Color findOpposition(Color playerColor);

	template<typename T>
	vector<vector<T>> getCombinationsOfSizeN(const vector<T> & source, int n)
	{
		vector<T> combination;
		vector<vector<T>> combinations;
		string bitmask(n, 1);
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
	vector<vector<T>> getCombinationsOfSizeKtoN(const vector<T> & source, const int k, const int n)
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