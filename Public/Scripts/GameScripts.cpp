#include "GameScripts.h"


GameScripts::GameScripts(sf::RenderWindow& window, Game& game)
{
	GameScripts::window = &window;
	GameScripts::game = &game;

	float pi = atan(1.0) * 4;

	//Poczatkowy setup gry, ladowanie siatek obiektow, itd.
	game.LoadNewMesh("asteroids_text.obj");
	game.LoadNewMesh("start_text.obj");
	game.LoadNewMesh("exit_text.obj");
	game.LoadNewMesh("rectangle.obj");

	objectTypes[0] = 0;
	stage = 0;
	menuSelection = 0;
}

GameScripts::~GameScripts()
{
}

void GameScripts::HandleEvents(std::vector<sf::Event> events)
{
	for (auto& event : events)
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Up && menuSelection < 5)
					menuSelection += 1;
				if (event.key.code == sf::Keyboard::Down && menuSelection > 0)
					menuSelection -= 1;
				std::cout << menuSelection << '\n';
		}
	}
}

void GameScripts::Update(float deltaTime)
{

	//Przykladowy input klawiszy

	if (stage == 0)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			game->camera.rotation.z += 1 * deltaTime;
		}

	}
	if (stage == 0 && game->objCount < 3)
	{
		PositionData objLocation;
		objLocation.position = Node{ 0, 2, 3 };
		objLocation.rotation = Node{ 0, 0, 0 };

		game->AddNewObject(game->objectMeshNames["asteroids_text.obj"], objLocation, 0, sf::Color(255, 255, 255, 255), 0.5, true, false, true);
		objLocation.position.y -= 1.5;

		game->AddNewObject(game->objectMeshNames["rectangle.obj"], objLocation, 1, sf::Color(255, 255, 255, 50), 0.5, true, false, true);
		game->AddNewObject(game->objectMeshNames["start_text.obj"], objLocation, 0, sf::Color(255, 255, 255, 255), 0.5, true, false, true);
		objLocation.position.y -= 1.5;

		game->AddNewObject(game->objectMeshNames["rectangle.obj"], objLocation, 1, sf::Color(255, 255, 255, 50), 0.5, true, false, true);
		game->AddNewObject(game->objectMeshNames["exit_text.obj"], objLocation, 0, sf::Color(255, 255, 255, 255), 0.5, true, false, true);
	}

	for (int i = 0; i < game->objCount; i++)
	{
	}
}
