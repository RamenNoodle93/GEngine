#include <iostream>

#include "SFML-2.6.1/include/SFML/Graphics.hpp"
#include "Tools/CommonHeaders.h"
#include "../Public/Scripts/GameScripts.h"
#include "Tools/Include/Game.h"
#include "../Public/Scripts/Settings.h"

//Glowna funkcja
int main()
{
	Game game(size.x / size.y);

	//Pobieranie ustawien z pliku i tworzenie okna

	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), name);
	GameScripts mainGame(window, game);

	while (window.isOpen())
	{

		sf::Event event;

		std::vector<sf::Event> events;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			events.push_back(event);

		}

		float deltaTime = clock.restart().asSeconds();

		mainGame.HandleEvents(events);
		mainGame.Update(deltaTime);

		std::vector<Projected> projected = game.Projection();
		window.clear(sf::Color::Black);

		for (auto& obj : projected)
		{

			Tools::DrawTriangle(obj, window, obj.outline, obj.solid, obj.color);

		}
		window.display();

	}

	return 0;
}