#pragma once
#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void run();
protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	Player* m_player;
	Enemy* m_enemy;
	sf::RenderWindow m_window;

};
