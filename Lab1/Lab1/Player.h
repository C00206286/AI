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

	private:
		sf::CircleShape playerCircle;
		sf::Vector2f velocity;
		sf::Vector2f position;
		int radius;
		sf::Texture playerTexture;
		sf::Sprite playerSprite;

};

