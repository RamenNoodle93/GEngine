#pragma once

#include "Object.h"

class Cube :
	public Object
{
public:
	Cube(Node pos, Node rot);
	~Cube();
};

