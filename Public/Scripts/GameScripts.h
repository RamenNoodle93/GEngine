#pragma once

#include "../../Private/Tools/Include/Game.h"
#include "../../Private/Tools/CommonHeaders.h"


class GameScripts
{
public:
	GameScripts(sf::RenderWindow& window, Game& game);
	~GameScripts();

	void HandleEvents();
	void Update(float deltaTime);

private:
	sf::RenderWindow* window;
	Game* game;
};