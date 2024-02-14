#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <strstream>

#define PI 3.14159265358979323846

struct Node {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
};

struct Point {
	float x, y;
};

struct PositionData {
	Node rotation;
	Node position;
};

struct Triangle {
	Node p[3];
};

struct Triangle2D {
	Point p[3];
};

struct Mesh
{
	std::vector<Triangle> tris;

	bool LoadFromObjectFile(std::string sFilename)
	{

		std::ifstream file(sFilename);
		if (!file.is_open())
			return false;

		//Tymczasowy zbiór punktów
		std::vector<Node> vertices;

		while (!file.eof())
		{
			char line[128];
			file.getline(line, 128);

			std::strstream s;
			s << line;

			char junk;

			if (line[0] == 'v')
			{
				Node v;
				s >> junk >> v.x >> v.y >> v.z;
				vertices.push_back(v);
			}

			if (line[0] == 'f')
			{
				int f[3];
				s >> junk >> f[0] >> f[1] >> f[2];

				tris.push_back({ vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1] });
			}
		}

		return true;
	}

};

struct Mat4x4 {
	float m[4][4] = { 0.0f };
};