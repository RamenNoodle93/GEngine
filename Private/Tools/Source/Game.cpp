#include "../Include/Game.h"

//#include "../../../Public/Resources/"

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

	meshCount = 0;
	objCount = 0;

	projMat = Tools::GetProjectionMatrix(Game::aspectRatio, Game::fov, Game::zFar, Game::zNear);
}

Game::~Game()
{

}

std::vector<Projected> Game::Projection()
{
	Mat4x4 worldMatrixObject, worldMatrixCamera;
	Mat4x4 proj = Tools::GetProjectionMatrix(Game::aspectRatio, Game::fov, Game::zFar, Game::zNear);
	worldMatrixCamera = Tools::GetWorldMatrix(camera.rotation.x, camera.rotation.y, camera.rotation.z);

	std::vector<Projected> projectedObjs;

	for (int i = 0; i < objCount; i++)
	{
		std::cout << "Projecting object number: " << i << '\n';

		Object currentObj = objects[i];
		Mesh objMesh = meshes[currentObj.meshId];

		objects[i].location.rotation.y += 0.01;

		std::vector<Triangle> projectedTris;

		if (!currentObj.flat)
		{

			worldMatrixObject = Tools::GetWorldMatrix(currentObj.location.rotation.x, currentObj.location.rotation.y, currentObj.location.rotation.z);

			//Pozycja obiektu wzgledem kamery
			Node relativePosition;
			Tools::AddVectors(currentObj.location.position, camera.position, relativePosition);

			for (auto& tri : objMesh.tris)
			{

				Node faceNormal, temp;

				Triangle rotatedSelf, rotatedOrigin, translated, projected, tempTriangle;

				//Obracanie obiektu wokol samego siebie
				Tools::MatrixMultiplyTriangle(tri, worldMatrixObject, rotatedSelf);

				//Przesuwanie obiektu w swiecie
				Tools::TranslateTriangle(rotatedSelf, relativePosition, translated);

				//Obracanie obiektu wokol kamery
				Tools::MatrixMultiplyTriangle(translated, worldMatrixCamera, rotatedOrigin);

				//Usuwanie niewidocznych trojkatow, oraz przycinanie czesciowo widocznych trojkatow,
				//z wykorzystaniem punktow przeciecia z plaszczyzna
				int nClippedTriangles = 0;
				Triangle clipped[2];
				Node planeVec, planeNormal;

				planeVec = { 0.0f, 0.0f, 0.1f };
				planeNormal = { 0.0f, 0.0f, 0.1f };

				nClippedTriangles = Tools::ClipTriangle(planeVec, planeNormal, rotatedOrigin, clipped[0], clipped[1]);

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
			}
		}
		else
		{
			for (auto& tri : objMesh.tris)
			{
				Triangle temp;

				std::cout << currentObj.meshId << '\n';

				for (int i = 0; i < 3; i++) {
					temp.p[i] = Node{ tri.p[i].x * (-200) + 400, tri.p[i].y * (-200) + 400, tri.p[i].z };
				}

				projectedTris.push_back(temp);

			}

		}

		std::sort(projectedTris.begin(), projectedTris.end(), [](Triangle& tri1, Triangle& tri2)
				  {
					  float z1 = tri1.p[0].z + tri1.p[1].z + tri1.p[2].z;
					  float z2 = tri2.p[0].z + tri2.p[1].z + tri2.p[2].z;
					  return z1 > z2;
				  });

		projectedObjs.push_back(Projected{ currentObj.color , projectedTris, currentObj.location.position.z });

		std::cout << projectedTris.size() << '\n';

	}

	std::sort(projectedObjs.begin(), projectedObjs.end(), [](Projected& obj1, Projected& obj2)
			  {
				  return obj1.depth > obj2.depth;
			  });

	return projectedObjs;

}

idType Game::LoadNewMesh(std::string fileName) //Ladowanie siatki do tablicy 'meshes', funkcja zwraca id siatki
{
	Mesh tempMesh;
	std::string filePath = "./Public/Resources/" + fileName;
	tempMesh.LoadFromObjectFile(filePath);

	meshes[meshCount] = tempMesh;

	meshCount++;

	return meshCount - 1;
}

idType Game::AddNewObject(idType meshId, PositionData pos, bool entity, idType type, sf::Color color)
{
	Object tempObject = Object{ meshId, pos, entity, type , color };

	objects[objCount] = tempObject;
	objCount++;

	return objCount - 1;
}

idType Game::RemoveObjectFromId(idType idToDelete)
{
	Object dummyObj = Object{ 0, PositionData{Node{0,0,0}, Node{0,0,0}}, false, 0 };

	objects[idToDelete] = objects[objCount - 1];
	objects[objCount - 1] = dummyObj;

	objCount--;

	return objCount;
}
