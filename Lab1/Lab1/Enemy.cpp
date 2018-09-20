#include "Enemy.h"

Enemy::Enemy() :
	position(400, 600),
	velocity(0, 0),
	radius(50)
{

	enemyCircle.setFillColor(sf::Color::Black);
	enemyCircle.setPosition(800, 600);

	if (!enemyTexture.loadFromFile("Meteor.png"))
	{
		// Error...
	}

	srand(time(NULL));

	y = rand() % 10;
	x = rand() % 10;

	x = x / 10;
	y = y / 10;

	enemySprite.setScale(0.3f, 0.3f);
	enemySprite.setTexture(enemyTexture);
}

Enemy::~Enemy()
{
}

void Enemy::update(double dt)
{
	enemySprite.setPosition(enemyCircle.getPosition());
	enemyCircle.setPosition(enemyCircle.getPosition().x + x, enemyCircle.getPosition().y + y);

	//Window borders
	if (enemyCircle.getPosition().x > 1200)
	{
		enemyCircle.setPosition(-100, enemyCircle.getPosition().y);
	}
	if (enemyCircle.getPosition().x < -100)
	{
		enemyCircle.setPosition(1200, enemyCircle.getPosition().y);
	}
	if (enemyCircle.getPosition().y > 1200)
	{
		enemyCircle.setPosition(enemyCircle.getPosition().x, -100);
	}
	if (enemyCircle.getPosition().y < -100)
	{
		enemyCircle.setPosition(enemyCircle.getPosition().x, 1200);
	}
}
void Enemy::draw(sf::RenderWindow & window)
{
	window.draw(enemySprite);
}