#pragma once

#include <random>

#include "../../Private/Tools/Include/Game.h"
#include "../../Private/Tools/CommonHeaders.h"


class GameScripts
{
public:
	GameScripts(sf::RenderWindow& window, Game& game);
	~GameScripts();

	bool HandleEvents(std::vector<sf::Event> events);
	void Update(float deltaTime);

private:
	sf::RenderWindow* window;
	Game* game;
	int objectTypes[256];
	int menuSelection;
	int stage;
	int prevStage;
	int playerId;
	float acceleration;
	float velocityX;
	float velocityY;
};