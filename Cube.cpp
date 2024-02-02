#include "Cube.h"

//std::vector<Triangle> cubic = { Triangle(Node(), Node(), Node()) };

Cube::Cube(Node pos, Node rot) : Object(pos, rot)
{
	std::vector<Node> vertices{
		Node{-1, -1, -1},
		Node{-1, 1, -1},
		Node{-1, -1, 1},
		Node{-1, 1, 1},
		Node{1, -1, -1},
		Node{1, 1, -1},
		Node{1, -1, 1},
		Node{1, 1, 1},
	};
	std::vector<Edge> edges{
		Edge{0, 1},
		Edge{0, 2},
		Edge{1, 3},
		Edge{2, 3},
		Edge{4, 5},
		Edge{4, 6},
		Edge{5, 7},
		Edge{6, 7},
		Edge{0, 4},
		Edge{1, 5},
		Edge{2, 6},
		Edge{3, 7}
	};
	SetVertices(vertices);
	SetEdges(edges);
}

Cube::~Cube()
{

}
