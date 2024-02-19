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
	game.LoadNewMesh("asteroid.obj");

	objectTypes[0] = 0;
	stage = 0;
	prevStage = -1;
	menuSelection = 1;
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
				switch (stage)
				{
					//Obsluga klawiszy w menu, dla sterowania statkiem itp. zastosuj obsluge klawiszy w funkcji update
					//(ta funkcja obsluguje pojedyncze klikniecia klawiszy, funkcja update, np. przytrzymanie przycisku)
					case 0:
						if (event.key.code == sf::Keyboard::Up)
							menuSelection = (menuSelection - 2);
						if (event.key.code == sf::Keyboard::Down && menuSelection > 0)
							menuSelection = (menuSelection + 2);
						std::cout << menuSelection << '\n';
				}
		}
	}
}

void GameScripts::Update(float deltaTime)
{

	if (prevStage != stage)
	{
		for (int i = 0; i < game->objCount; i++)
		{
			game->RemoveObjectFromId(i);
		}
	}

	//Przykladowy input klawiszy

	switch (stage)
	{
		//Menu glowne
		case 0:
			if (prevStage != stage)
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

				prevStage = 0;
			}

			game->objects[1].color = sf::Color(255, 255, 255, 50);
			game->objects[3].color = sf::Color(255, 255, 255, 50);

			game->objects[menuSelection].color = sf::Color(255, 255, 255, 100);

			break;

			//
		//case 1:
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (stage != 0)
		{
			prevStage = stage;
			stage = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (stage != 1)
		{
			prevStage = stage;
			stage = 1;
		}

		game->camera.rotation.z += 1 * deltaTime;
	}


	if (stage == 0 && game->objCount < 1)
	{

	}

	for (int i = 0; i < game->objCount; i++)
	{

	}
}
