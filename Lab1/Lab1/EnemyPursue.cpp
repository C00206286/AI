#include "EnemyPursue.h"
#include <math.h>
#include <iostream>

EnemyPursue::EnemyPursue(Game &game, double maxSpeed, float timeToTarget, int behaviour,int positionX, int positionY) :
	m_game(&game),
	position(positionX, positionY),
	velocity(0, 0),
	radius(50),
	maxSpeed(maxSpeed),
	rotation(0.1),
	direction(0,0),
	speed(0),
	distance(0),
	timeToTarget(timeToTarget),
	maxTimePrediction(200),
	timePrediction(0),
	newTarget(0,0),
	angle(0),
	wanderOffset(100),
	wanderRate(1),
	wanderRadius(10),
	moved(false),
	behaviour(behaviour),
	count(0)
	//0.5
	//1000
{
	srand(time(NULL));
	enemyCircle.setFillColor(sf::Color::Black);

	if (!enemyTexture.loadFromFile("Meteor.png"))
	{
		// Error...
	}

	//srand(time(NULL));

	//y = rand() % 20 -10;
	//x = rand() % 20 -10;

	//x = x / 10;
	//y = y / 10;
	enemySprite.setOrigin(200, 200);
	enemySprite.setScale(0.3f, 0.3f);
	enemySprite.setTexture(enemyTexture);
	enemySprite.setPosition(position);

	if(!font.loadFromFile("font.ttf"))
	{
	}

	enemyText.setFont(font);
	enemyText.setStyle(sf::Text::Bold);
	enemyText.setCharacterSize(30);
	enemyText.setFillColor(sf::Color::White);
}

EnemyPursue::~EnemyPursue()
{
}
void EnemyPursue::Wander()
{
	float random = rand() % 10 + 1;
	//random = random - 20;
	random = random / 10;

	wanderOrientation = random * wanderRate;
	targetOrientation = wanderOrientation + rotation;

	target = enemySprite.getPosition() + (wanderOffset * normalise(velocity));
	std::cout << "Count =" << wanderCount << std::endl;
	if (wanderCount > 20)
	{
		target += wanderRadius * convertToVector(targetOrientation);
	}
	if (wanderCount < 20)
	{
		target -= wanderRadius * convertToVector(targetOrientation);
	}
	if (wanderCount > 40)
	{
		wanderCount = 0;
	}
	wanderCount = wanderCount + 1;

	seekTarget(target);

}
sf::Vector2f EnemyPursue::convertToVector(float tar)
{
	float radians = tar * 3.14 / 180;
	result.x = cos(radians);
	result.y = sin(radians);

	return result;
}
void EnemyPursue::seek()
{
	velocity = m_game->getPlayerPosition() - enemySprite.getPosition();
	velocity = normalise(velocity);
	velocity.x = velocity.x * maxSpeed;
	velocity.y = velocity.y * maxSpeed;
	rotation = getNewOrientation(rotation, velocity);
}
void EnemyPursue::Arrive()
{
	velocity = m_game->getPlayerPosition() - enemySprite.getPosition();
	if (length(velocity) < 1)
	{
		velocity.x = 0;
		velocity.y = 0;
	}
	else
	{

		velocity = velocity / timeToTarget;
		if (length(velocity) > maxSpeed)
		{
			velocity = normalise(velocity);
			velocity.x = velocity.x * maxSpeed;
			velocity.y = velocity.y * maxSpeed;
		}

		rotation = getNewOrientation(rotation, velocity);
	}
}
void EnemyPursue::Pursue()
{

	direction = m_game->getPlayerPosition() - enemySprite.getPosition();
	distance = length(direction);
	speed = length(velocity);

	if (speed <= distance / maxTimePrediction)
	{
		timePrediction = maxTimePrediction;
	}
	else 
	{
		timePrediction = distance / speed;
	}

	newTarget = m_game->getPlayerPosition() + m_game->getPlayerVelocity()  * timePrediction;
	//std::cout << "Target x = " << newTarget.x << std::endl;
	//std::cout << "Player x = " << m_game->getPlayerPosition().x << std::endl;

	seekTarget(newTarget);
	
}
void EnemyPursue::flee()
{
	velocity = enemySprite.getPosition() - m_game->getPlayerPosition();
	velocity = normalise(velocity);
	velocity.x = velocity.x * maxSpeed;
	velocity.y = velocity.y * maxSpeed;
	rotation = getNewOrientation(rotation, velocity);
	fleeCount = fleeCount + 1;
	if (fleeCount > 500)
	{
		fleeBool = false;
		fleeCount = 0;
	}
}

void EnemyPursue::coneOfVision(sf::Vector2f targetPosition)
{

	double DirectionMeToVelocity = atan2((velocity.y + enemySprite.getPosition().y) - enemySprite.getPosition().y, (velocity.x + enemySprite.getPosition().x) - enemySprite.getPosition().x);
	double DirectionEnemyToMe = atan2(targetPosition.y - enemySprite.getPosition().y, targetPosition.x - enemySprite.getPosition().x);
	double Angle_ACB = DirectionMeToVelocity - DirectionEnemyToMe;


	const double Pi = acos(-1);  
	if (Angle_ACB > Pi) Angle_ACB -= 2 * Pi;
	else if (Angle_ACB < -Pi) Angle_ACB += 2 * Pi;

	Angle_ACB = Angle_ACB * 180 / 3.14;
	if (Angle_ACB < 90 && Angle_ACB > -90)
	{
		if (getDistance(enemySprite.getPosition(), targetPosition) < 100)
		{
			fleeBool = true;
		}
	}
}
float EnemyPursue::dotProduct(sf::Vector2f vector1, sf::Vector2f vector2)
{
	float dotProduct = (vector1.x * vector2.x) + (vector1.y * vector2.y);
	return dotProduct;
}

void EnemyPursue::fleeTarget(sf::Vector2f targi)
{
	velocity = enemySprite.getPosition() - targi;
	velocity = normalise(velocity);
	velocity.x = velocity.x * maxSpeed;
	velocity.y = velocity.y * maxSpeed;
	rotation = getNewOrientation(rotation, velocity);
	fleeCount = fleeCount + 1;
	if (fleeCount > 500)
	{
		fleeBool = false;
		fleeCount = 0;
	}
}

void EnemyPursue::seekTarget(sf::Vector2f targ)
{
	velocity = targ - enemySprite.getPosition();
	velocity = normalise(velocity);
	velocity.x = velocity.x * maxSpeed;
	velocity.y = velocity.y * maxSpeed;
	rotation = getNewOrientation(rotation, velocity);
}

float EnemyPursue::getNewOrientation(float currentOrientation, sf::Vector2f velocity)
{
	if (length(velocity) > 0)
	{
		float rotation = atan2(-velocity.x, velocity.y) * 180 / 3.14;
		return rotation;
	}
	else
	{
		return currentOrientation;
	}
}
sf::Vector2f EnemyPursue::normalise(sf::Vector2f vector)
{
	//length = sqrt((ax * ax) + (ay * ay) + (az * az))
	float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	//divide each by length
	if (length != 0)
	{
		vector.x = vector.x / length;
		vector.y = vector.y / length;
	}
	return vector;

}
float EnemyPursue::getDistance(sf::Vector2f point1, sf::Vector2f point2)
{
	distanceGot = sqrt(((point2.x - point1.x)*(point2.x - point1.x)) + ((point2.y - point1.y)*(point2.y - point1.y)));
	return distanceGot;
}
sf::Vector2f EnemyPursue::getPursuePosition()
{
	return enemySprite.getPosition();
}
float EnemyPursue::length(sf::Vector2f vector)
{
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

void EnemyPursue::findClosest()
{
	distance1 = getDistance(m_game->getEnemyPosition(), enemySprite.getPosition());
	distance2 = getDistance(enemySprite.getPosition(), m_game->getEnemy2Position());
	distance3 = getDistance(enemySprite.getPosition(), m_game->getEnemy3Position());
	distance4 = getDistance(enemySprite.getPosition(), m_game->getEnemy4Position());
	distance5 = getDistance(enemySprite.getPosition(), m_game->getEnemyPursuePosition());
	if (distance1 == 0)
	{
		distance1 = 100000;
	}
	if (distance2 == 0)
	{
		distance2 = 100000;
	}
	if (distance3 == 0)
	{
		distance3 = 100000;
	}
	if (distance4 == 0)
	{
		distance4 = 100000;
	}
	if (distance5 == 0)
	{
		distance5 = 100000;
	}
	if (distance1 < distance2 && distance1 < distance3 && distance1 < distance4 && distance1 < distance5)
	{
		coneOfVision(m_game->getEnemyPosition());
		fleeFrom = m_game->getEnemyPosition();
	}
	if (distance2 < distance1 && distance2 < distance3 && distance2 < distance4 && distance2 < distance5)
	{
		coneOfVision(m_game->getEnemy2Position());
		fleeFrom = m_game->getEnemy2Position();
	}
	if (distance3 < distance2 && distance3 < distance1 && distance3 < distance4 && distance3 < distance5)
	{
		coneOfVision(m_game->getEnemy3Position());
		fleeFrom = m_game->getEnemy3Position();
	}
	if (distance4 < distance2 && distance4 < distance1 && distance4 < distance3 && distance4 < distance5)
	{
		coneOfVision(m_game->getEnemy4Position());
		fleeFrom = m_game->getEnemy4Position();
	}
	if (distance5 < distance1 && distance5 < distance2 && distance5 < distance3 && distance5 < distance4)
	{
		coneOfVision(m_game->getEnemyPursuePosition());
		fleeFrom = m_game->getEnemyPursuePosition();
	}
}
void EnemyPursue::update(double dt)
{
	enemyText.setPosition(enemySprite.getPosition().x - 40, enemySprite.getPosition().y + 50);
	if (behaviour == 4)
	{
		enemyText.setString("Pursue");
		findClosest();
		if(fleeBool == false)
		{
			Pursue();
		}
		if (fleeBool == true)
		{
			fleeTarget(fleeFrom);
		}
		
	}
	if (behaviour == 3)
	{
		enemyText.setString("Wander");
		findClosest();
		if (fleeBool == false)
		{
			if (count == 0)
			{
				//seek();
				Wander();
			}
			count = count + 1;
			if (count > 50)
			{
				count = 0;
			}
		}
		if (fleeBool == true)
		{
			fleeTarget(fleeFrom);
		}
	}
	if (behaviour == 1)
	{
		enemyText.setString("Arrive");
		findClosest();
		if (fleeBool == false)
		{
			Arrive();
		}
		if (fleeBool == true)
		{
			fleeTarget(fleeFrom);
		}
	}
	if (behaviour == 2)
	{
		enemyText.setString("Seek");
		findClosest();
		if (fleeBool == false)
		{
			seek();
		}
		if (fleeBool == true)
		{
			fleeTarget(fleeFrom);
		}
	}

	enemySprite.setPosition(enemySprite.getPosition().x + velocity.x, enemySprite.getPosition().y + velocity.y);
	enemySprite.setRotation(rotation);

	//Window borders
	if (enemySprite.getPosition().x > 2200)
	{
		enemySprite.setPosition(-100, enemySprite.getPosition().y);
	}
	if (enemySprite.getPosition().x < -100)
	{
		enemySprite.setPosition(2200, enemySprite.getPosition().y);
	}
	if (enemySprite.getPosition().y > 2200)
	{
		enemySprite.setPosition(enemySprite.getPosition().x, -100);
	}
	if (enemySprite.getPosition().y < -100)
	{
		enemySprite.setPosition(enemySprite.getPosition().x, 2200);
	}
}
void EnemyPursue::draw(sf::RenderWindow & window)
{
	window.draw(enemySprite);
	window.draw(enemyText);
}