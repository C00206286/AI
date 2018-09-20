#include "Game.h"

// Updates per milliseconds
static double const MS_PER_UPDATE = 1.0;

Game::Game()
	: m_window(sf::VideoMode(1200, 1200), "Brendans Game :)")

{

	m_window.setVerticalSyncEnabled(true);
	m_player = new Player();
	m_enemy = new Enemy();
}

void Game::update(double dt)
{
	sf::Time deltaTime;
	m_player->update(dt);
	m_enemy->update(dt);
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0));
	m_player->draw(m_window);
	m_enemy->draw(m_window);
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