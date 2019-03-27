#pragma once
#include <algorithm>
#include <iostream>
#include "Common.h"


namespace cephalopod
{
	
	using namespace std;
	string directionEnumToString(Direction direction);

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
	vector<vector<T>> getCombinationsOfSizeKToN(const vector<T> & source, int k, int n)
	{
		vector<vector<T>> combinations;
		for (int i = k; i <= n; ++i)
		{
			vector<Capture> temp = getCombinationsOfSizeN(source, i);
			combinations.insert(std::end(combinations), std::begin(temp), std::end(temp));
		}
		return combinations;
	}
}