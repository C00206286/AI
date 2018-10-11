#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 1.0;

Game::Game()
	: m_window(sf::VideoMode(2200, 2200), "Brendans Game :)")

{

	m_window.setVerticalSyncEnabled(true);
	m_player = new Player();
	m_enemyArrive = new EnemyPursue(*this, 0.4,1000,1, 200, 200);
	m_enemyArrive2 = new EnemyPursue(*this,0.9,2000,1, 600, 900);
	m_enemy2 = new EnemyPursue(*this,0.5,1000,2, 900, 200);
	m_enemy3 = new EnemyPursue(*this,0.7,1000,3, 450, 450);
	m_enemyPursue = new EnemyPursue(*this, 0.5, 1000,4, 1000, 1000);

}

void Game::update(double dt)
{
	sf::Time deltaTime;
	m_player->update(dt);
	m_enemyArrive->update(dt);
	m_enemyArrive2->update(dt);
	m_enemy2->update(dt);
	m_enemy3->update(dt);
	m_enemyPursue->update(dt);
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0));
	m_player->draw(m_window);
	m_enemyArrive->draw(m_window);
	m_enemyArrive2->draw(m_window);
	m_enemy2->draw(m_window);
	m_enemy3->draw(m_window);
	m_enemyPursue->draw(m_window);
	m_window.display();
}
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
	
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

void Game::processGameEvents(sf::Event& event)
{


}
sf::Vector2f Game::getPlayerPosition()
{
	return m_player->getPlayerPosition();
}
sf::Vector2f Game::getEnemyPosition()
{
	return m_enemyArrive->getPursuePosition();
}
sf::Vector2f Game::getEnemy2Position()
{
	return m_enemyArrive2->getPursuePosition();
}
sf::Vector2f Game::getEnemy3Position()
{
	return m_enemy2->getPursuePosition();
}
sf::Vector2f Game::getEnemy4Position()
{
	return m_enemy3->getPursuePosition();
}
sf::Vector2f Game::getEnemyPursuePosition()
{
	return m_enemyPursue->getPursuePosition();
}
sf::Vector2f Game::getPlayerVelocity()
{
	return m_player->getVelocity();
}