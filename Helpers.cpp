#include "Helpers.h"

namespace cephalopod
{
	using namespace std;
	string directionEnumToString(Direction direction)
	{
		switch (direction)
		{
		case cephalopod::up:
			return "up";
		case cephalopod::right:
			return "right";
		case cephalopod::down:
			return "down";
		case cephalopod::left:
			return "left";
		}
		return "";
	}

	//template<typename T>
	//vector<vector<T>> generateCombinations(vector<T> source)
	//{
	//	vector<T> combination;
	//	vector<vector<T>> combinations;

	//	// n = 0, left = 0, right = 0
	//	// 1
	//	// n = 0, left = 0, right = 1
	//	// 1 2
	//	// 

	//	for (int n = 0; n < source.size(); ++n)
	//	{
	//		for (int left = 0; left < source.size(); ++left)
	//		{
	//			for (int right = n; right < source.size(); ++right)
	//			{
	//				combination.push_back(source[right]);
	//			}
	//			combinations.push_back(combination);
	//			combination.clear();
	//		}
	//	}

	//	cout << "printing\n";
	//	vector<T> temp;
	//	for (int n = 0; n < source.size(); ++n)
	//	{
	//		temp = combinations[n];
	//		for (int left = 0; left < source.size(); ++left)
	//		{
	//			cout << temp[left] << " ";
	//		}
	//		cout << "\n";
	//	}

	//	return ;
	//}
}
