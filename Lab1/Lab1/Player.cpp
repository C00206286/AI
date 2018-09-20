#include "Player.h"

Player::Player() :
	position(800, 600),
	velocity(0, 0),
	radius(50)
{
	
	playerCircle.setFillColor(sf::Color::Black);
	playerCircle.setPosition(800, 600);

	if (!playerTexture.loadFromFile("rocket.png"))
	{
		// Error...
	}

	playerSprite.setScale(0.05f, 0.05f);
	playerSprite.setTexture(playerTexture);
}

Player::~Player()
{
}

void Player::update(double dt)
{
	playerSprite.setPosition(playerCircle.getPosition());

	//Keyboard input to change velocity
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = velocity.x - 0.001;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = velocity.x + 0.001;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = velocity.y - 0.001;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y = velocity.y + 0.001;
	}

	//Apply velocity
	playerCircle.setPosition(playerCircle.getPosition().x + velocity.x, playerCircle.getPosition().y + velocity.y);

	//Window borders
	if (playerCircle.getPosition().x > 1200)
	{
		playerCircle.setPosition(-100, playerCircle.getPosition().y);
	}
	if (playerCircle.getPosition().x < -100)
	{
		playerCircle.setPosition(1200, playerCircle.getPosition().y);
	}
	if (playerCircle.getPosition().y > 1200)
	{
		playerCircle.setPosition(playerCircle.getPosition().x, -100);
	}
	if (playerCircle.getPosition().y < -100)
	{
		playerCircle.setPosition(playerCircle.getPosition().x, 1200);
	}
}
void Player::draw(sf::RenderWindow & window)
{
	window.draw(playerSprite);
}
