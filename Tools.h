#pragma once

#include "Types.h"

class Tools
{
public:
	Tools();
	~Tools();
	static void MultiplyMatrixVector(Node& i, Node& o, Mat4x4& m);

	static Node AddVectors(Node& vec1, Node& vec2);
	//static Node CalculateNormal(Triangle& triangle);
	static Mat4x4 Mulitply4x4Matrices(Mat4x4& mat1, Mat4x4& mat2);

	static Mat4x4 GetRotationMatrixX(float rotationX);
	static Mat4x4 GetRotationMatrixY(float rotationY);
	static Mat4x4 GetRotationMatrixZ(float rotationZ);
};

