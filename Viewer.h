#pragma once
#include "Model.h"

class Viewer
{
public:
	Viewer(Model* model);
	~Viewer();
private:
	Model* model;
};

