#include "Die.h"



Die::Die()
{
}

Die::Die(AdjacencyMap<Die*> adjacencyMap)
{
	this->adjacencyMap = adjacencyMap;
}


Die::~Die()
{
}

void Die::print()
{
	std::cout << "test\n";
	for (int i = 0; i < ADJACENCY_MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < ADJACENCY_MATRIX_SIZE; ++j)
		{
			
			if (adjacencyMap[i][j] != nullptr && adjacencyMap[i][j]->getPip() == 0)
				std::cout << " ";
			else if (adjacencyMap[i][j] != nullptr)
				std::cout << "?";
			else
				std::cout << "X";

		}
		std::cout << std::endl;
	}
}

int Die::getPip() const
{
	return pip;
}

void Die::setPip(int value)
{
	//TODO: post condition
	this->pip = value;
}
