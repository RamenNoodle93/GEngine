#pragma once

#include "../../Private/Tools/Include/Game.h"
#include "../../Private/Tools/CommonHeaders.h"


class GameScripts
{
public:
	GameScripts(sf::RenderWindow& window, Game& game);
	~GameScripts();

	void Update(float deltaTime, std::vector<sf::Event> events);

private:
	sf::RenderWindow* window;
	Game* game;
	int objectTypes[4096];
};