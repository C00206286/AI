#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class Player
{
	public:
		Player();
		~Player();
		void update(double dt);
		void draw(sf::RenderWindow & window);
		float getNewOrientation(float currentOrientation, sf::Vector2f velocity);
		sf::Vector2f getVelocity();
		sf::Vector2f getPlayerPosition();

	private:
		sf::Vector2f position;
		sf::CircleShape playerCircle;
		sf::Vector2f velocity;
		sf::Vector2f heading;
		int radius;
		sf::Texture playerTexture;
		sf::Sprite playerSprite;
		float orientation;
		float rotation;
		double speed;

};

