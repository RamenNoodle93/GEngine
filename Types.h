#pragma once

#include <vector>

struct Node {
	float x, y, z;
};

struct Point {
	float x, y;
};

struct ProjectionData {
	Node rotation;
	Node position;
};

struct Triangle {
	Node p[3];
};

struct Mesh {
	std::vector<Triangle> tris;
};

struct Mat4x4 {
	float m[4][4] = { 0.0f };
};