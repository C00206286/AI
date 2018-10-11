#pragma once
#include "Player.h"
#include "EnemyPursue.h"
#include <SFML/Graphics.hpp>

class Enemy;
class Enemy2;
class Enemy3;
class EnemyPursue;
class Player;

class Game
{
public:
	Game();
	void run();
	sf::Vector2f getPlayerPosition();
	sf::Vector2f getPlayerVelocity();
	sf::Vector2f getEnemyPosition();
	sf::Vector2f getEnemy2Position();
	sf::Vector2f getEnemy3Position();
	sf::Vector2f getEnemy4Position();
	sf::Vector2f getEnemyPursuePosition();

protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);
	Player* m_player;
	EnemyPursue* m_enemyArrive;
	EnemyPursue* m_enemy2;
	EnemyPursue* m_enemy3;
	EnemyPursue* m_enemyArrive2;
	EnemyPursue* m_enemyPursue;
	sf::RenderWindow m_window;

};
