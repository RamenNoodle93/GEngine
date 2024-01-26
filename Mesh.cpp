#include "Mesh.h"

Mesh::Mesh(std::vector<Node> nodes, std::vector<Triangle> tris)
{
	nodeList = &nodes;
	edgeList = &tris;
}

Mesh::~Mesh()
{
}

