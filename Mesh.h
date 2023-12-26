#pragma once

#include "Types.h"
#include <vector>

class Mesh
{

public:
	std::vector<Node>* nodeList;
	std::vector<Edge>* edgeList;
	Mesh(std::vector<Node> nodes, std::vector<Edge> edges);
	~Mesh();

};

