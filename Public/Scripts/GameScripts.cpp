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
	game.LoadNewMesh("settings_text.obj");
	game.LoadNewMesh("ship.obj");

	objectTypes[0] = 0;
	stage = 0;
	prevStage = -1;
	menuSelection = 1;
	acceleration = 0;
	velocityX = 0;
	velocityY = 0;
}

GameScripts::~GameScripts()
{
}

bool GameScripts::HandleEvents(std::vector<sf::Event> events)
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
						{
							menuSelection = (menuSelection - 2) % 6;
							if (menuSelection < 0)
								menuSelection = 5;
						}

						if (event.key.code == sf::Keyboard::Down)
						{
							menuSelection = (menuSelection + 2) % 6;
						}

						if (event.key.code == sf::Keyboard::Enter)
						{
							switch (menuSelection)
							{
								case 1:
									prevStage = stage;
									stage = 1;
									break;
								case 3:
									prevStage = stage;
									stage = 2;
									break;
								case 5:
									return false;
									break;
							}
						}

						std::cout << menuSelection << '\n';
				}
		}
	}
	return true;
}

void GameScripts::Update(float deltaTime)
{

	if (prevStage != stage)
	{
		for (int i = 0; i < 4096; i++)
		{
			game->ResetObjectFromId(i);
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
				objLocation.position = Node{ 0, -300, 0 };
				objLocation.rotation = Node{ 0, 0, 0 };

				game->AddNewObject(game->objectMeshNames["asteroids_text.obj"], objLocation, 0, sf::Color(255, 255, 255, 255), 0.5, true, false, true);

				objLocation.position.y += 150;
				game->AddNewObject(game->objectMeshNames["rectangle.obj"], objLocation, 1, sf::Color(255, 255, 255, 50), 0.5, true, false, true);
				game->AddNewObject(game->objectMeshNames["start_text.obj"], objLocation, 0, sf::Color(255, 255, 255, 255), 0.35, true, false, true);

				objLocation.position.y += 150;
				game->AddNewObject(game->objectMeshNames["rectangle.obj"], objLocation, 1, sf::Color(255, 255, 255, 50), 0.5, true, false, true);
				game->AddNewObject(game->objectMeshNames["settings_text.obj"], objLocation, 0, sf::Color(255, 255, 255, 255), 0.35, true, false, true);

				objLocation.position.y += 150;
				game->AddNewObject(game->objectMeshNames["rectangle.obj"], objLocation, 1, sf::Color(255, 255, 255, 50), 0.5, true, false, true);
				game->AddNewObject(game->objectMeshNames["exit_text.obj"], objLocation, 0, sf::Color(255, 255, 255, 255), 0.35, true, false, true);

				std::random_device random;
				std::mt19937 generator(random());

				std::uniform_real_distribution<> distr(-400, 400);

				for (int i = 0; i < 50; i++)
				{
					PositionData asteroidLocation;

					float xRand = distr(generator);
					float yRand = distr(generator);

					asteroidLocation.position = Node{ xRand, -400 + yRand, -1 };
					asteroidLocation.rotation = Node{ 0, 0, -5 };

					game->AddNewObject(game->objectMeshNames["asteroid.obj"], asteroidLocation, 2, sf::Color(255, 255, 255, 255), 0.005f, true, true, true);

				}

				prevStage = 0;
			}

			game->objects[1].color = sf::Color(255, 255, 255, 50);
			game->objects[3].color = sf::Color(255, 255, 255, 50);
			game->objects[5].color = sf::Color(255, 255, 255, 50);

			game->objects[menuSelection].color = sf::Color(255, 255, 255, 100);

			for (int i = 0; i < game->objCount; i++)
			{
				if (game->objects[i].typeId == 2)
				{
					game->objects[i].location.position.y += 100 * deltaTime;
					if (game->objects[i].location.position.y > 400)
						game->objects[i].location.position.y = -400;
				}
			}

			break;

			//Glowna czesc gry
		case 1:
			if (prevStage != stage)
			{
				velocityX = 0;
				velocityY = 0;
				acceleration = 0;

				PositionData startLocation;
				startLocation.position = Node{ 0,0,0 };
				startLocation.rotation = Node{ 0,0,0 };

				CollisionObject collider;

				playerId = game->AddNewObject(game->objectMeshNames["ship.obj"], startLocation, 3, sf::Color(255, 255, 255, 255), 0.09f, true, true, true);

				for (int i = 0; i < game->meshes[game->objectMeshNames["ship.obj"]].tris.size(); i++)
				{
					for (int j = 0; j < 2; j++)
					{
						collider.points.push_back(Point{ game->meshes[game->objectMeshNames["ship.obj"]].tris[i].p[j].x, game->meshes[game->objectMeshNames["ship.obj"]].tris[i].p[j].x });
					}
				}

				prevStage = 1;
			}

			if (velocityX > 0)
				velocityX -= 1 * deltaTime;

			if (velocityY > 0)
				velocityY -= 1 * deltaTime;

			if (velocityX < 0)
				velocityX += 1 * deltaTime;

			if (velocityY < 0)
				velocityY += 1 * deltaTime;

			int asteroids = 0;

			for (int i = 0; i < game->objCount; i++)
			{
				if (game->objects[i].typeId == 2)
				{
					asteroids++;
				}

				if (game->objects[i].typeId == 3)
				{
					game->objects[i].location.position.x += velocityX * deltaTime;
					game->objects[i].location.position.y += velocityY * deltaTime;

					game->objects[i].collider.posData = Position2D{ game->objects[i].location.position.x, game->objects[i].location.position.y,game->objects[i].location.rotation.z };

					for (int j = 0; j < game->objects[i].collider.points.size(); i++)
					{
						game->objects[i].collider.vertices.push_back(Point{});
					}

				}
				if (game->objects[i].location.position.x > 400)
					game->objects[i].location.position.x = -400;
				else if (game->objects[i].location.position.x < -400)
					game->objects[i].location.position.x = 400;

				if (game->objects[i].location.position.y > 400)
					game->objects[i].location.position.y = -400;
				else if (game->objects[i].location.position.y < -400)
					game->objects[i].location.position.y = 400;
			}

			std::cout << asteroids << '\n';

			if (asteroids < 5)
			{
				PositionData positionstuff;
				positionstuff.position = Node{ 0,0,0 };
				positionstuff.rotation = Node{ 0,0,0 };

				game->AddNewObject(game->objectMeshNames["asteroid.obj"], positionstuff, 2, sf::Color(255, 255, 255, 255), 0.01f, true, true, true);
			}

			break;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{

		if (stage == 1)
		{
			float velocityMag = sqrtf(pow(velocityX, 2) + pow(velocityY, 2));

			if (velocityMag < 300)
			{
				velocityX += sinf(game->objects[playerId].location.rotation.z) * deltaTime * 100;
				velocityY -= cosf(game->objects[playerId].location.rotation.z) * deltaTime * 100;
			}
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (stage == 1)
		{
			game->objects[playerId].location.rotation.z += 3 * deltaTime;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (stage == 1)
		{
			game->objects[playerId].location.rotation.z -= 3 * deltaTime;
		}
	}

	if (stage == 0 && game->objCount < 1)
	{

	}

	for (int i = 0; i < game->objCount; i++)
	{

	}
}
