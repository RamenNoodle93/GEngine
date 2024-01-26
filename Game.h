#pragma once

#include <cmath>
#include "Types.h"

class Game
{
private:
	float zNear;
	float zFar;
	float fov;
	float aspectRatio;
	float fovTan;
	Mat4x4 projMat;
	Mat4x4 rotationMatX;
	Mat4x4 rotationMatY;
	Mat4x4 rotationMatZ;
	Objects objectList;
public:
	Game(float aspectRatio, float rotX = 0.0f, float rotY = 0.0f, float rotZ = 0.0f, float zNear = 0.1f, float zFar = 1000.0f, float fov = 90.0f);
	~Game();
	Mat4x4 GetProj();

	Mat4x4 GetRotX();
	Mat4x4 GetRotY();
	Mat4x4 GetRotZ();

	Objects GetProjected();

	float rotationX;
	float rotationY;
	float rotationZ;
};

