#pragma once

#include <vector>

struct Node {
	float x;
	float y;
	float z;
};

struct Point {
	float x;
	float y;
};

struct Edge {
	int point1;
	int point2;
};

struct ProjectionData {
	Node rotation;
	Node position;
};

struct ProjectedObject {
	std::vector<Point> points;
	std::vector<Edge> edges;
};

struct Mat4x4 {
	float m[4][4] = { 0.0f };
};