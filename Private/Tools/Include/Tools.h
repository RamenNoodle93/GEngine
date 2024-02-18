#pragma once

#include "Types.h"
#include "../CommonHeaders.h"

class Tools
{
public:
	Tools();
	~Tools();

	idType GetIndex(idType id);
	idType GetGeneration(idType id);
	idType ConstructId(int index, int generation);

	static void AddVectors(Node& vec1, Node& vec2, Node& out);
	static void SubtractVectors(Node& vec1, Node& vec2, Node& out);
	static void NormalizeVector(Node& vec, Node& out);
	static void DivideVector(Node& vec, float scale, Node& out);
	static void MultiplyVector(Node& vec, float scale, Node& out);

	static Node VectorPlaneIntersect(Node& planeVec, Node& planeNormal, Node& lineStart, Node& lineEnd);

	static float DotProduct(Node& first, Node& second);

	static void MultiplyMatrixVector(Node& in, Node& out, Mat4x4& matrix);
	static void CalculateNormal(Triangle& in, Node& out);
	static void TranslateTriangle(Triangle& in, Node& pos, Triangle& out);
	static void MatrixMultiplyTriangle(Triangle& in, Mat4x4& matrix, Triangle& out);

	static Mat4x4 GetProjectionMatrix(float aspectRatio, float fov, float zFar, float zNear);

	static Mat4x4 GetWorldMatrix(float rotationX, float rotationY, float rotationZ);
	static Mat4x4 GetRotationMatrixX(float rotationX);
	static Mat4x4 GetRotationMatrixY(float rotationY);
	static Mat4x4 GetRotationMatrixZ(float rotationZ);
	static Mat4x4 Mulitply4x4Matrices(Mat4x4& mat1, Mat4x4& mat2);

	static int ClipTriangle(Node& planeVec, Node& planeNormal, Triangle& in, Triangle& out1, Triangle& out2);

	static void DrawTriangle(Projected projection, sf::RenderWindow& window);
};

