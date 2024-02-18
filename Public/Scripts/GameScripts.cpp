#include "GameScripts.h"


GameScripts::GameScripts(sf::RenderWindow& window, Game& game)
{
	GameScripts::window = &window;
	GameScripts::game = &game;

	//Poczatkowy setup gry, ladowanie siatek obiektow, itd.
	game.LoadNewMesh("teapot.obj");

	objectTypes[0] = 0;

}

GameScripts::~GameScripts()
{
}

void GameScripts::Update(float deltaTime, std::vector<sf::Event> events)
{

	//Przykladowy input klawiszy
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		game->camera.position.z -= 1 * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		game->camera.rotation.y += 1 * deltaTime;
	}

	if (game->objCount < 1)
	{
		PositionData objLocation;

		objLocation.position = Node{ 0,0,4 };
		objLocation.rotation = Node{ 0,0,0 };

		game->AddNewObject(game->objectMeshNames["teapot.obj"], objLocation, false, 0, sf::Color(255, 0, 255, 255));
	}

	for (int i = 0; i < game->objCount; i++)
	{

		if (game->objects[i].typeId == 1)
			game->objects[i].location.rotation.y += 1 * deltaTime;
	}
}
