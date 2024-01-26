#pragma once

#include <vector>
#include "Mesh.h"

struct Node {
	float x;
	float y;
	float z;
};

struct Point {
	float x;
	float y;
};

struct Triangle {
	int point1;
	int point2;
	int point3;
};

struct Mat4x4 {
	float m[4][4] = { 0.0f };
};

struct Objects {
	std::vector<Mesh> obj;
};