#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

class Game;

class EnemyPursue
{
public:
	EnemyPursue(Game &game, double maxSpeed, float timeToTarget, int behaviour, int positionX, int positionY);
	~EnemyPursue();
	void update(double dt);
	void draw(sf::RenderWindow & window);
	void seek();
	void Arrive();
	void flee();
	void Pursue();
	void seekTarget(sf::Vector2f);
	void fleeTarget(sf::Vector2f);
	void LeaveTarget(sf::Vector2f);
	sf::Vector2f getPursuePosition();


private:
	void Wander();
	int behaviour = 0;
	sf::Vector2f heading;
	sf::Vector2f fleeFrom;
	sf::Text enemyText;
	sf::Font font;
	Game * m_game;
	sf::CircleShape enemyCircle;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f direction;
	int radius;
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	sf::ConvexShape coneTriangle;
	float coneAngle;
	float coneLength;
	double x;
	double y;
	double rotation;
	double maxSpeed;
	float timeToTarget;
	float distance;
	float speed;
	float count;
	bool moved;
	float maxTimePrediction;
	float timePrediction;
	sf::Vector2f newTarget;
	sf::Vector2f normalise(sf::Vector2f vector);
	sf::Vector2f target;
	sf::Vector2f result;
	float length(sf::Vector2f vector);
	float getNewOrientation(float currentOrientation, sf::Vector2f velocity);
	float dotProduct(sf::Vector2f vector1, sf::Vector2f vector2);
	float getDistance(sf::Vector2f point1, sf::Vector2f point2);
	float angle;
	void coneOfVision(sf::Vector2f targetPosition);
	void findClosest();
	float distance1 = 0;
	float distance2 = 0;
	float distance3 = 0;
	float distance4 = 0;
	float distance5 = 0;
	float distanceGot = 0;
	bool fleeBool = false;
	float fleeCount = 0;
	float wanderOffset;
	float wanderRate;
	float targetOrientation;
	float wanderRadius;
	float wanderOrientation;
	float wanderCount = 0;
	sf::Vector2f convertToVector(float);

};