#include <iostream>

#include "SFML-2.6.1/include/SFML/Graphics.hpp"
#include "Tools/CommonHeaders.h"
#include "../Public/Scripts/Script.h"
#include "Tools/Include/Game.h"

Game* game;

//Glowna funkcja
int main()
{
	game = new Game(size.x / size.y);

	//Pobieranie ustawien z pliku i tworzenie okna

	sf::RenderWindow window(sf::VideoMode(size.x, size.y), name);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		std::vector<Triangle> projected = game->Update();

		//std::cout << projected.size();

		for (auto& projection : projected)
		{
			sf::Vertex line1[] =
			{
				sf::Vertex(sf::Vector2f(projection.p[0].x, projection.p[0].y)),
				sf::Vertex(sf::Vector2f(projection.p[1].x, projection.p[1].y))
			};

			window.draw(line1, 2, sf::Lines);

			sf::Vertex line2[] =
			{
				sf::Vertex(sf::Vector2f(projection.p[1].x, projection.p[1].y)),
				sf::Vertex(sf::Vector2f(projection.p[2].x, projection.p[2].y))
			};

			window.draw(line2, 2, sf::Lines);

			sf::Vertex line3[] =
			{
				sf::Vertex(sf::Vector2f(projection.p[0].x, projection.p[0].y)),
				sf::Vertex(sf::Vector2f(projection.p[2].x, projection.p[2].y))
			};

			window.draw(line3, 2, sf::Lines);
		}

		window.display();

	}

	return 0;
}