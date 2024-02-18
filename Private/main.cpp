#include <iostream>

#include "SFML-2.6.1/include/SFML/Graphics.hpp"
#include "Tools/CommonHeaders.h"
#include "../Public/Scripts/GameScripts.h"
#include "Tools/Include/Game.h"
#include "../Public/Scripts/Settings.h"

Game* game;

//Glowna funkcja
int main()
{
	game = new Game(size.x / size.y);

	//Pobieranie ustawien z pliku i tworzenie okna

	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), name);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float deltaTime = clock.restart().asSeconds();



		std::vector<Projected> projected = game->Projection();
		window.clear(sf::Color::Black);

		for (auto& obj : projected)
		{

			Tools::DrawTriangle(obj, window);

		}
		window.display();

	}

	return 0;
}