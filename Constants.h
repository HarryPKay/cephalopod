#pragma once
#include <vector>
#include <map>

namespace cephalopod
{
	template <typename T>
	using AdjacencyMap = std::map<int, std::map<int, T>>;

	template <typename T>
	using Matrix = std::vector<std::vector<T>>;

	//typedef std::map<int, std::map<int, Die*>> AdjacencyMap;
	///typedef std::vector<std::vector<Die>> Matrix;

	const int N_MAX = 9;
	const int M_MIN = 3;
	const int MIN_PIP = 1;
	const int MAX_PIP = 6;
	const int NO_DICE = 0;
	const int ADJACENCY_MATRIX_SIZE = 3;
	const char MOVE_SEPARATOR = ' ';
}