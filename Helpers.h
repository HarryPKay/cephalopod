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

	/*
	* Generates all possible sets of combinations for the given set of elements.
	* For example, given the set {1,2,3} and n = 2, the following would be returned:
	* { { 1, 2}, {1, 3}, {2, 3} }
	* 
	* @param n The size of the combinations.
	* @return The vector of combinations generated.
	*/
	template <typename T>
	vector<vector<T>> findCombinationsOfSizeN(const vector<T>& source, uint32_t n)
	{
		vector<T> combination;
		vector<vector<T>> combinations;

		// Create a bit mask of size n so that only a size of n elements will form the set.
		string bitmask(n, 1);
		// Add trailing zeroes so that the mask is the same size as source.
		bitmask.resize(source.size(), 0);

		// Keep adding combinations for each permutation of the mask.
		do
		{
			for (auto i = 0; i < source.size(); ++i)
			{
				// Grab elements that correspond to the position of the ones in the bit mask.
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

	/*
	* Generates all possible variable length sets of combinations for the given set
	* of elements. For example, given the set { 1, 2, 3}, k = 1, n = 2, the following
	* sets would be returned:
	* { {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3} }
	* 
	* @param source The set containing elements.
	* @param k Restricts generated sets to a minimum of size k.
	* @param n Restricts generated sets to a maximum of size m.
	* @return a vector of the sets.
	*/
	template <typename T>
	vector<vector<T>> findCombinationsOfSizeKtoN(const vector<T>& source, const uint32_t k, const uint32_t n)
	{
		// Vary the size of k and generate a fixed size set of n combinations.
		vector<vector<T>> combinations;
		for (auto i = k; i <= n; ++i)
		{
			vector<Captures> temp = findCombinationsOfSizeN(source, i);
			combinations.insert(std::end(combinations), std::begin(temp), std::end(temp));
		}
		return combinations;
	}
}
