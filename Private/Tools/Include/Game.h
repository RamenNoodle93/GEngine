#pragma once

#include <cmath>
#include <algorithm>

#include "../CommonHeaders.h"

class Game
{
private:
	float zNear;
	float zFar;
	float fov;
	float aspectRatio;
	PositionData camera;
	Mat4x4 projMat;
	Mat4x4 rotationMatX;
	Mat4x4 rotationMatY;
	Mat4x4 rotationMatZ;

	Mesh meshes[4096];

public:
	Game(float aspectRatio, float zNear = 0.1f, float zFar = 1000.0f, float fov = 90.0f);
	~Game();
	std::vector<Triangle> Update();
	PositionData objPos;
};

