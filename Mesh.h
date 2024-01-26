#pragma once

#include <vector>
#include "Types.h"

class Mesh
{

public:
	Mesh(std::vector<Node> nodes, std::vector<Triangle> tris);
	~Mesh();

	std::vector<Node>* nodeList;
	std::vector<Triangle>* edgeList;
};

