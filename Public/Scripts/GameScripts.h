#pragma once

#include "../../Private/Tools/CommonHeaders.h"


class GameScripts
{
public:
	GameScripts(sf::RenderWindow& window);
	~GameScripts();

	void HandleEvents();
	void Update();

private:
	sf::RenderWindow* window;
};