#pragma once

#include "Types.h"

class Tools
{
public:
	Tools();
	~Tools();
	static void MultiplyMatrixVector(Node& i, Node& o, Mat4x4& m);
	static Mat4x4 GetRotationMatrixX(float rotationX);
	static Mat4x4 GetRotationMatrixY(float rotationY);
	static Mat4x4 GetRotationMatrixZ(float rotationZ);
};

