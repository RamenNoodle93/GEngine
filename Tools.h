#pragma once

#include "Types.h"

class Tools
{
public:
	Tools();
	~Tools();

	static bool ShapeOverlap_SAT(object2d& r1, object2d& r2);

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

	static bool CheckCollision(object2d& obj1, object2d& obj2);

	static std::vector<Point> GetAxes(object2d& obj);
	static Point GetPerpendicular(Point vect);
	static Point GetNormalVec2D(Point vect);

	static bool SATcollision(object2d& obj1, object2d& obj2);

	static Projection Project(Point& axis, object2d& obj);

	static bool Overlap(Projection& p1, Projection& p2);

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
};

