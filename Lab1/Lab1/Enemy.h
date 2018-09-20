#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy();
	~Enemy();
	void update(double dt);
	void draw(sf::RenderWindow & window);

private:
	sf::CircleShape enemyCircle;
	sf::Vector2f velocity;
	sf::Vector2f position;
	int radius;
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	double x;
	double y;

};