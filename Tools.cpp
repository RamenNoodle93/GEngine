#include "Tools.h"

Tools::Tools()
{
}

Tools::~Tools()
{
}

void Tools::MultiplyMatrixVector(Node& i, Node& o, Mat4x4& m)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
}

Node Tools::AddVectors(Node& vec1, Node& vec2)
{
	Node added;
	added.x = vec1.x + vec2.x;
	added.y = vec1.y + vec2.y;
	added.z = vec1.z + vec2.z;
	return added;
}

//Node Tools::CalculateNormal(Triangle& triangle)
//{
//
//}

Mat4x4 Tools::Mulitply4x4Matrices(Mat4x4& mat1, Mat4x4& mat2)
{
	Mat4x4 multiplied;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
				multiplied.m[i][j] += mat1.m[i][k] * mat2.m[k][j];
		}
	}
	return multiplied;
}

Mat4x4 Tools::GetRotationMatrixX(float rotationX)
{
	Mat4x4 rotationMatX;
	rotationMatX.m[0][0] = 1.0f;
	rotationMatX.m[1][1] = cosf(rotationX);
	rotationMatX.m[1][2] = sinf(rotationX);
	rotationMatX.m[2][1] = -sinf(rotationX);
	rotationMatX.m[2][2] = cosf(rotationX);
	rotationMatX.m[3][3] = 1.0f;

	return rotationMatX;
}

Mat4x4 Tools::GetRotationMatrixY(float rotationY)
{
	Mat4x4 rotationMatY;
	rotationMatY.m[0][0] = cosf(rotationY);
	rotationMatY.m[0][2] = -sinf(rotationY);
	rotationMatY.m[1][1] = 1.0f;
	rotationMatY.m[2][0] = sinf(rotationY);
	rotationMatY.m[2][2] = cosf(rotationY);
	rotationMatY.m[3][3] = 1.0f;

	return rotationMatY;
}

Mat4x4 Tools::GetRotationMatrixZ(float rotationZ)
{
	Mat4x4 rotationMatZ;
	rotationMatZ.m[0][0] = cosf(rotationZ);
	rotationMatZ.m[0][1] = -sinf(rotationZ);
	rotationMatZ.m[1][0] = sinf(rotationZ);
	rotationMatZ.m[1][1] = cosf(rotationZ);
	rotationMatZ.m[2][2] = 1.0f;
	rotationMatZ.m[3][3] = 1.0f;

	return rotationMatZ;
}
