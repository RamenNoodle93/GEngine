#pragma once

#include "Types.h"

class Object
{
private:
	std::vector<Node> vertex;
	std::vector<Edge> edge;
public:
	Object(Node pos, Node rot);
	~Object();
	void SetVertices(std::vector<Node> nodes);
	void SetEdges(std::vector<Edge> edges);

	std::vector<Node> GetVertices();
	std::vector<Edge> GetEdges();

	Node rotation;
	Node position;
};

