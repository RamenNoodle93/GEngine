#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <strstream>
#include <stdint.h>

//Liczby calkowite bez znaku
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

//Liczby calkowite
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using idType = u32;

constexpr u32 indexSize{ 16 };
constexpr u32 generationSize{ sizeof(idType) * 8 - indexSize };

constexpr idType indexMask{ (idType { 1 } << indexSize) - 1 };
constexpr idType generationMask{ ~((idType { 1 } << generationSize) - 1) };

struct Object
{
	idType meshId;
	//PositionData location;
};

struct Node
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
};

struct Point
{
	float x, y;
};

struct PositionData
{
	Node rotation;
	Node position;
};

struct Triangle
{
	Node p[3];
};

struct Triangle2D
{
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

		//Tymczasowy zbi�r punkt�w
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

struct Mat4x4
{
	float m[4][4] = { 0.0f };
};