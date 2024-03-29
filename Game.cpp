#include "Game.h"

Game::Game(float aspectRatio, float zNear, float zFar, float fov)
{
	//Dane startowe
	float pi = atan(1.0) * 4;
	Game::zNear = zNear;
	Game::zFar = zFar;
	Game::fov = fov * pi / 180.0f;
	Game::aspectRatio = aspectRatio;

	Node pos;
	pos.x = 0.0f;
	pos.y = -1.0f;
	pos.z = 0.0f;

	Node rot;
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;

	camera.rotation = rot;
	camera.position = pos;

	objPos.position = { 0.0f, 0.0f, 4.0f };
	objPos.rotation = { 0.0f, 0.0f, 0.0f };

	projMat = Tools::GetProjectionMatrix(Game::aspectRatio, Game::fov, Game::zFar, Game::zNear);

}

Game::~Game()
{

}

std::vector<Triangle> Game::Update()
{
	objPos.rotation.y += 0.01;
	camera.position.z -= 0.03;
	Mat4x4 proj = Tools::GetProjectionMatrix(Game::aspectRatio, Game::fov, Game::zFar, Game::zNear);

	std::vector<Triangle> projectedTris;

	Mesh loadedObj;

	loadedObj.LoadFromObjectFile("teapot.obj");

	Mat4x4 worldMatrixObject, worldMatrixCamera;

	worldMatrixObject = Tools::GetWorldMatrix(objPos.rotation.x, objPos.rotation.y, objPos.rotation.z);

	worldMatrixCamera = Tools::GetWorldMatrix(camera.rotation.x, camera.rotation.y, camera.rotation.z);

	for (auto& tri : loadedObj.tris)
	{

		Node relativePosition, faceNormal, temp;

		//Pozycja obiektu wzgledem kamery
		Tools::AddVectors(objPos.position, camera.position, relativePosition);

		Triangle rotatedSelf, rotatedOrigin, translated, projected, tempTriangle;

		//Obracanie obiektu wokol samego siebie
		Tools::MatrixMultiplyTriangle(tri, worldMatrixObject, rotatedSelf);

		//Przesuwanie obiektu w swiecie
		Tools::TranslateTriangle(rotatedSelf, relativePosition, translated);

		//Obracanie obiektu wokol kamery
		Tools::MatrixMultiplyTriangle(translated, worldMatrixCamera, rotatedOrigin);

		/*Tools::CalculateNormal(rotatedOrigin, faceNormal);
		Tools::NormalizeVector(faceNormal, faceNormal);

		temp.x = rotatedOrigin.p[0].x - camera.position.x;
		temp.y = rotatedOrigin.p[0].y - camera.position.y;
		temp.z = rotatedOrigin.p[0].z - camera.position.z;*/

		//Sprawdzanie czy trojkat jest widoczny (obecnie wylaczone)

		//if (Tools::DotProduct(faceNormal, temp) < 0.0f)
		//{

		int nClippedTriangles = 0;
		Triangle clipped[2];
		Node planeVec, planeNormal;

		planeVec = { 0.0f, 0.0f, 0.1f };
		planeNormal = { 0.0f, 0.0f, 0.1f };

		nClippedTriangles = Tools::ClipTriangle(planeVec, planeNormal, rotatedOrigin, clipped[0], clipped[1]);

		// We may end up with multiple triangles form the clip, so project as
		// required
		for (int n = 0; n < nClippedTriangles; n++)
		{
			Triangle scaled;
			Tools::MatrixMultiplyTriangle(clipped[n], projMat, projected);

			Tools::DivideVector(projected.p[0], projected.p[0].w, scaled.p[0]);
			Tools::DivideVector(projected.p[1], projected.p[1].w, scaled.p[1]);
			Tools::DivideVector(projected.p[2], projected.p[2].w, scaled.p[2]);

			for (int i = 0; i < 3; i++) {
				tempTriangle.p[i] = Node{ scaled.p[i].x * (-200) + 400, scaled.p[i].y * (-200) + 400, scaled.p[i].z };
			}

			projectedTris.push_back(tempTriangle);
		}
		//}
	}

	std::sort(projectedTris.begin(), projectedTris.end(), [](Triangle& tri1, Triangle& tri2)
			  {
				  float z1 = tri1.p[0].z + tri1.p[1].z + tri1.p[2].z;
				  float z2 = tri2.p[0].z + tri2.p[1].z + tri2.p[2].z;
				  return z1 > z2;
			  });

	return projectedTris;

}
