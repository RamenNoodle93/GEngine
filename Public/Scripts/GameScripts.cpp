#include "GameScripts.h"


GameScripts::GameScripts(sf::RenderWindow& window, Game& game)
{
	GameScripts::window = &window;
	GameScripts::game = &game;

	game.LoadNewMesh("teapot.obj");

}

GameScripts::~GameScripts()
{
}

void GameScripts::HandleEvents()
{

}

void GameScripts::Update(float deltaTime)
{

	if (game->objCount < 1)
	{
		PositionData objLocation;

		objLocation.position = Node{ 0,0,4 };
		objLocation.rotation = Node{ 0,0,0 };

		game->AddNewObject(0, objLocation, false, 0, sf::Color(255, 0, 255, 255));
	}


	for (int i = 0; i < game->objCount; i++)
	{
		if (game->objects[i].location.rotation.y > 1)
		{
			game->RemoveObjectFromId(0);
		}
	}
}
