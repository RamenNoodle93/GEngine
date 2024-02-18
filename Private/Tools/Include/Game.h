#pragma once

#include <cmath>
#include <algorithm>

#include "SFML/Graphics.hpp"
#include "../CommonHeaders.h"

class Game
{
private:
	float zNear;
	float zFar;
	float fov;
	float aspectRatio;
	Mat4x4 projMat;
	Mat4x4 rotationMatX;
	Mat4x4 rotationMatY;
	Mat4x4 rotationMatZ;

public:
	Game(float aspectRatio, float zNear = 0.1f, float zFar = 1000.0f, float fov = 60.0f);
	~Game();
	std::vector<Projected> Projection();
	idType LoadNewMesh(std::string fileName);
	idType AddNewObject(idType meshId, PositionData pos, idType type, sf::Color color, float scale = 1.0f, bool flat = false, bool outline = true, bool solid = false);
	idType RemoveObjectFromId(idType idToDelete);

	PositionData camera;
	int objCount;
	int meshCount;
	Object objects[4096];
	Mesh meshes[512];

	std::map<std::string, int> objectMeshNames;
};

