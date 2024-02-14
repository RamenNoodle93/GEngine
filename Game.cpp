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

	//G³ówna macierz rzutuj¹ca
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

std::vector<Triangle2D> Game::Update()
{
	Mat4x4 proj = GetProj();

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

	std::vector<Triangle2D> projectedTris;

	PositionData objPos;
	objPos.position = { 0.0f, 0.0f, 5.0f };
	objPos.rotation = { PI, 0.0f, 0.0f };

	Mesh loadedObj;

	loadedObj.LoadFromObjectFile("teapot.obj");

	for (auto& tri : loadedObj.tris)
	{

		camera.rotation.z += 0.00001f;

		Node relativePosition = Tools::AddVectors(objPos.position, camera.position);

		Triangle rotatedSelf, rotatedOrigin, translated, projected;

		Triangle2D tempTriangle;

		Mat4x4 rotationMatrixX, rotationMatrixY, rotationMatrixZ, temp, worldMatrix;

		rotationMatrixX = Tools::GetRotationMatrixX(objPos.rotation.x);
		rotationMatrixY = Tools::GetRotationMatrixY(objPos.rotation.y);
		rotationMatrixZ = Tools::GetRotationMatrixZ(objPos.rotation.z);

		temp = Tools::Mulitply4x4Matrices(rotationMatrixY, rotationMatrixZ);

		worldMatrix = Tools::Mulitply4x4Matrices(rotationMatrixX, temp);

		Tools::MultiplyMatrixVector(tri.p[0], rotatedSelf.p[0], worldMatrix);
		Tools::MultiplyMatrixVector(tri.p[1], rotatedSelf.p[1], worldMatrix);
		Tools::MultiplyMatrixVector(tri.p[2], rotatedSelf.p[2], worldMatrix);

		translated.p[0] = Tools::AddVectors(relativePosition, rotatedSelf.p[0]);
		translated.p[1] = Tools::AddVectors(relativePosition, rotatedSelf.p[1]);
		translated.p[2] = Tools::AddVectors(relativePosition, rotatedSelf.p[2]);

		rotationMatrixX = Tools::GetRotationMatrixX(camera.rotation.x);
		rotationMatrixY = Tools::GetRotationMatrixY(camera.rotation.y);
		rotationMatrixZ = Tools::GetRotationMatrixZ(camera.rotation.z);

		temp = Tools::Mulitply4x4Matrices(rotationMatrixY, rotationMatrixZ);

		worldMatrix = Tools::Mulitply4x4Matrices(rotationMatrixX, temp);

		Tools::MultiplyMatrixVector(translated.p[0], rotatedOrigin.p[0], worldMatrix);
		Tools::MultiplyMatrixVector(translated.p[1], rotatedOrigin.p[1], worldMatrix);
		Tools::MultiplyMatrixVector(translated.p[2], rotatedOrigin.p[2], worldMatrix);

		Tools::MultiplyMatrixVector(rotatedOrigin.p[0], projected.p[0], projMat);
		Tools::MultiplyMatrixVector(rotatedOrigin.p[1], projected.p[1], projMat);
		Tools::MultiplyMatrixVector(rotatedOrigin.p[2], projected.p[2], projMat);

		for (int i = 0; i < 3; i++) {
			tempTriangle.p[i] = Point{ projected.p[i].x * 200 + 400, projected.p[i].y * 200 + 400 };
		}

		projectedTris.push_back(tempTriangle);
	}
	return projectedTris;

}
