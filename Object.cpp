#include "Object.h"

Object::Object(Node pos, Node rot)
{
	vertex = std::vector<Node>();
	edge = std::vector<Edge>();
	rotation = rot;
	position = pos;
}

Object::~Object()
{

}

std::vector<Node> Object::GetVertices()
{
	return vertex;
}

std::vector<Edge> Object::GetEdges()
{
	return edge;
}

void Object::SetVertices(std::vector<Node> nodes)
{
	vertex = nodes;
}

void Object::SetEdges(std::vector<Edge> edges)
{
	edge = edges;
}

