#pragma once

#include <cmath>

#include "Types.h"
#include "Cube.h"
#include "Object.h"
#include "Tools.h"

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
	std::vector<Object*> structures;
public:
	Game(float aspectRatio, float zNear = 0.1f, float zFar = 1000.0f, float fov = 90.0f);
	~Game();
	Mat4x4 GetProj();
	Mat4x4 GetRotX();
	Mat4x4 GetRotY();
	Mat4x4 GetRotZ();
	std::vector<ProjectedObject> Update();
	ProjectionData camera;
};

