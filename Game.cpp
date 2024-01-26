#include "Game.h"

Game::Game(float aspectRatio, float rotX, float rotY, float rotZ, float zNear, float zFar, float fov)
{
	//Dane startowe
	float pi = atan(1.0) * 4;
	Game::zNear = zNear;
	Game::zFar = zFar;
	Game::fov = fov * pi / 180.0f;
	Game::fovTan = 1.0f / tanf(Game::fov * 0.5f);
	Game::aspectRatio = aspectRatio;

	rotationX = rotX;
	rotationY = rotY;
	rotationZ = rotZ;

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

Mat4x4 Game::GetRotX()
{
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
	rotationMatZ.m[0][0] = cosf(rotationZ);
	rotationMatZ.m[0][1] = -sinf(rotationZ);
	rotationMatZ.m[1][0] = sinf(rotationZ);
	rotationMatZ.m[1][1] = cosf(rotationZ);
	rotationMatZ.m[2][2] = 1.0f;
	rotationMatZ.m[3][3] = 1.0f;

	return rotationMatZ;
}

Objects Game::GetProjected() {

}