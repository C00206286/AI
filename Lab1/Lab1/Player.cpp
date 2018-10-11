#include "Player.h"
#include <iostream>
#include <math.h>

Player::Player() :
	position(800, 600),
	velocity(0, 0),
	heading(0,0),
	speed(0),
	radius(50),
	orientation(0),
	rotation(0.1)
{
	
	playerCircle.setFillColor(sf::Color::Black);
	playerSprite.setPosition(800, 600);

	if (!playerTexture.loadFromFile("rocket.png"))
	{
		// Error...
	}

	//684,1261
	playerSprite.setOrigin(630.5, 342);
	playerSprite.setScale(0.05f, 0.05f);
	playerSprite.setTexture(playerTexture);
}

Player::~Player()
{
}

sf::Vector2f Player::getPlayerPosition()
{
	return playerSprite.getPosition();
}
sf::Vector2f Player::getVelocity()
{
	velocity.x = heading.x * speed;
	velocity.y = heading.y * speed;
	return velocity;
}

void Player::update(double dt)
{
	//orientation = getNewOrientation(orientation,velocity);

	//if (playerSprite.getRotation() >= orientation + 1 || playerSprite.getRotation() <= orientation -1)
	//{
	//	playerSprite.rotate(rotation);
	//}

	//Keyboard input to change velocity
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//velocity.x = velocity.x - 0.001;
		playerSprite.rotate(-0.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//velocity.x = velocity.x + 0.001;
		playerSprite.rotate(0.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		//velocity.y = velocity.y - 0.001;
		if (speed < 1)
		{
			speed = speed + 0.01;
		}
	}
	else
	{
		if (speed > 0)
		{
			speed = speed - 0.001;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed > -1)
		{
			speed = speed - 0.01;
		}
	}
	else
	{
		if (speed < 0)
		{
			speed = speed + 0.001;
		}
	}

	//Apply velocity
	float radians = playerSprite.getRotation()*3.14159 / 180;
	heading.x = (cos(radians));
	heading.y = (sin(radians));
	playerSprite.setPosition(playerSprite.getPosition().x + (heading.x * speed), playerSprite.getPosition().y + (heading.y * speed));
	//std::cout << speed << std::endl;

	//Window borders
	if (playerSprite.getPosition().x > 2200)
	{
		playerSprite.setPosition(-100, playerSprite.getPosition().y);
	}
	if (playerSprite.getPosition().x < -100)
	{
		playerSprite.setPosition(2200, playerSprite.getPosition().y);
	}
	if (playerSprite.getPosition().y > 2200)
	{
		playerSprite.setPosition(playerSprite.getPosition().x, -100);
	}
	if (playerSprite.getPosition().y < -100)
	{
		playerSprite.setPosition(playerSprite.getPosition().x, 2200);
	}
}
float Player::getNewOrientation(float currentOrientation, sf::Vector2f velocity)
{
	if (velocity.x != 0 || velocity.y != 0)
	{
		return ((atan2(velocity.x, velocity.y))*(180/ 3.14159));
	}
	else
	{
		return currentOrientation;
	}
}
void Player::draw(sf::RenderWindow & window)
{
	window.draw(playerSprite);
}

