#pragma once

#include "Types.h"

class Tools
{
public:
	Tools();
	~Tools();
	static void MultiplyMatrixVector(Node& i, Node& o, Mat4x4& m);
};

