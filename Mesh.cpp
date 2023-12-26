#include "Mesh.h"

Mesh::Mesh(std::vector<Node> nodes, std::vector<Edge> edges)
{
	nodeList = &nodes;
	edgeList = &edges;
}

Mesh::~Mesh()
{
}

