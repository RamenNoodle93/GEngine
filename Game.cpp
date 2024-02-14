#include "Game.h"

Game::Game(float aspectRatio, float zNear, float zFar, float fov)
{
	//Dane startowe
	float pi = atan(1.0) * 4;
	Game::zNear = zNear;
	Game::zFar = zFar;
	Game::fov = fov * pi / 180.0f;
	Game::fovTan = 1.0f / tanf(Game::fov * 0.5f);
	Game::aspectRatio = aspectRatio;

	Node pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	Node rot;
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;

	camera.rotation = rot;
	camera.position = pos;

	//G��wna macierz rzutuj�ca
	projMat.m[0][0] = Game::aspectRatio * Game::fovTan;
	projMat.m[1][1] = Game::fovTan;
	projMat.m[2][2] = Game::zFar / (Game::zFar - Game::zNear);
	projMat.m[3][2] = (-Game::zFar * Game::zNear) / (Game::zFar - Game::zNear);
	projMat.m[2][3] = 1.0f;
	projMat.m[3][3] = 0.0f;

}

Game::~Game()
{

}

Mat4x4 Game::GetProj()
{
	return Game::projMat;
}

Mat4x4 Game::GetRotX()
{
	float rotationX = camera.rotation.x;
	rotationMatX.m[0][0] = 1.0f;
	rotationMatX.m[1][1] = cosf(rotationX);
	rotationMatX.m[1][2] = sinf(rotationX);
	rotationMatX.m[2][1] = -sinf(rotationX);
	rotationMatX.m[2][2] = cosf(rotationX);
	rotationMatX.m[3][3] = 1.0f;

	return rotationMatX;
}

Mat4x4 Game::GetRotY()
{
	float rotationY = camera.rotation.y;
	rotationMatY.m[0][0] = cosf(rotationY);
	rotationMatY.m[0][2] = -sinf(rotationY);
	rotationMatY.m[1][1] = 1.0f;
	rotationMatY.m[2][0] = sinf(rotationY);
	rotationMatY.m[2][2] = cosf(rotationY);
	rotationMatY.m[3][3] = 1.0f;

	return rotationMatY;
}

Mat4x4 Game::GetRotZ()
{
	float rotationZ = camera.rotation.z;
	rotationMatZ.m[0][0] = cosf(rotationZ);
	rotationMatZ.m[0][1] = -sinf(rotationZ);
	rotationMatZ.m[1][0] = sinf(rotationZ);
	rotationMatZ.m[1][1] = cosf(rotationZ);
	rotationMatZ.m[2][2] = 1.0f;
	rotationMatZ.m[3][3] = 1.0f;

	return rotationMatZ;
}

std::vector<Point> Game::Update()
{
	Mat4x4 proj = GetProj();

	Mat4x4 rotx = GetRotX();
	Mat4x4 roty = GetRotY();
	Mat4x4 rotz = GetRotZ();

	camera.position.z -= 0.01;

	Mesh meshCube;
	meshCube.tris = {

		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
	};

	float rotationX = 0.0f, rotationY = 0.0f, rotationZ = 0.0f;

	std::vector<Point> projectedPoints;

	ProjectionData fullpos;
	fullpos.position = { -0.5f, -0.5f, 1.0f };

	for (auto& tri : meshCube.tris)
	{
		Mat4x4 rotationObjX = Tools::GetRotationMatrixX(rotationX);
		Mat4x4 rotationObjY = Tools::GetRotationMatrixY(rotationY);
		Mat4x4 rotationObjZ = Tools::GetRotationMatrixZ(rotationZ);

		Triangle translated, projected, rotatedX, rotatedY, rotatedZ;

		Tools::MultiplyMatrixVector(tri.p[0], rotatedX.p[0], rotationObjX);
		Tools::MultiplyMatrixVector(tri.p[1], rotatedX.p[1], rotationObjX);
		Tools::MultiplyMatrixVector(tri.p[2], rotatedX.p[2], rotationObjX);

		Tools::MultiplyMatrixVector(rotatedX.p[0], rotatedY.p[0], rotationObjY);
		Tools::MultiplyMatrixVector(rotatedX.p[1], rotatedY.p[1], rotationObjY);
		Tools::MultiplyMatrixVector(rotatedX.p[2], rotatedY.p[2], rotationObjY);

		Tools::MultiplyMatrixVector(rotatedY.p[0], rotatedZ.p[0], rotationObjZ);
		Tools::MultiplyMatrixVector(rotatedY.p[1], rotatedZ.p[1], rotationObjZ);
		Tools::MultiplyMatrixVector(rotatedY.p[2], rotatedZ.p[2], rotationObjZ);

		translated.p[0] = Tools::AddVectors(fullpos.position, rotatedZ.p[0]);
		translated.p[1] = Tools::AddVectors(fullpos.position, rotatedZ.p[1]);
		translated.p[2] = Tools::AddVectors(fullpos.position, rotatedZ.p[2]);

		Tools::MultiplyMatrixVector(translated.p[0], projected.p[0], projMat);
		Tools::MultiplyMatrixVector(translated.p[1], projected.p[1], projMat);
		Tools::MultiplyMatrixVector(translated.p[2], projected.p[2], projMat);

		for (int i = 0; i < 3; i++) {

			projectedPoints.push_back(Point{ projected.p[i].x * 50 + 400, projected.p[i].y * 50 + 400 });

		}
	}
	return projectedPoints;

	//for (auto object : structures) {

	//Mat4x4 rotationObjX = Tools::GetRotationMatrixX(object->rotation.x);
	//Mat4x4 rotationObjY = Tools::GetRotationMatrixY(object->rotation.y);
	//Mat4x4 rotationObjZ = Tools::GetRotationMatrixZ(object->rotation.z);
	/*
	for (auto& node : object->GetVertices())
	{
		Node rotatedNodeXObject, rotatedNodeYObject, rotatedNodeZObject, translatedNode, rotatedNodeXCamera, rotatedNodeYCamera, rotatedNodeZCamera, projectedNode;

		Tools::MultiplyMatrixVector(node, rotatedNodeXObject, rotationObjX);
		Tools::MultiplyMatrixVector(rotatedNodeXObject, rotatedNodeYObject, rotationObjY);
		Tools::MultiplyMatrixVector(rotatedNodeYObject, rotatedNodeZObject, rotationObjZ);

		translatedNode = Node{
			rotatedNodeZObject.x + camera.position.x + object->position.x,
			rotatedNodeZObject.y + camera.position.y + object->position.y,
			rotatedNodeZObject.z + camera.position.z + object->position.z
		};

		Tools::MultiplyMatrixVector(translatedNode, rotatedNodeXCamera, rotx);
		Tools::MultiplyMatrixVector(rotatedNodeXCamera, rotatedNodeYCamera, roty);
		Tools::MultiplyMatrixVector(rotatedNodeYCamera, rotatedNodeZCamera, rotz);

		Tools::MultiplyMatrixVector(rotatedNodeZCamera, projectedNode, proj);

		projectedNode.x *= 200;
		projectedNode.y *= 200;

		projectedNode.x += 400.0f;
		projectedNode.y += 400.0f;

		objectVertices.push_back(Point{ projectedNode.x, projectedNode.y });
	}
	*/
	//}
}
