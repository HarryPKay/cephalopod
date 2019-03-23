#pragma once
#include <iostream>
#include "Color.h"
#include "Constants.h"

using namespace cephalopod;

class Die
{
public:
	Die();
	Die(AdjacencyMap<Die*> adjacencyMap);
	AdjacencyMap<Die*> adjacencyMap;
	~Die();
	void print();
	int getPip() const;
	void setPip(int value);
private:
	int pip = NO_DICE;
	Color color = none;
};

