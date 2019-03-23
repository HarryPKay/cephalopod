#pragma once
#include "Viewer.h"
#include "Model.h"

class Controller
{
public:
	Controller(Viewer* viewer, Model* model);
	Controller();
	~Controller();

private:
	Viewer* viewer;
	Model* model;
};

