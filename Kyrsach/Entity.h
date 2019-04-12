#pragma once
#include<vector>
#include<SFML/Graphics.hpp>

#include"Level.h"
#include"Animation.h"

class Magic;

class Entity
{
public:
	enum Direction
	{
		Left, Right, Stay_Left, Stay_Right, Jump, Jump_Left, Jump_Right
	};
	virtual~Entity();
	Entity(double x, double y);
	Entity(double x, double y, double width, double height);
	virtual void Update(double time) = 0;
	virtual void Draw(sf::RenderWindow &window);
	virtual void setHealth(double health);
	virtual void setMaxHealth(double MaxHealth);
	virtual void SetDamage(Magic *magic);
	virtual void SetDamage(double damage);
	virtual int getHealth();
	virtual int getMaxHealth();

protected:
	double x, y;
	double width, height;
	double health;
	double MaxHealth;
	bool isAlive;
	bool isHurt;
	sf::RectangleShape rect;
	Animation animation;
	Direction direction;
	double Speed;
	bool OnGround;
	bool EnableJump;
	double JumpTime;
	double currentJumpTime;
	double powerJump;
	b2Body *body;
	b2World *world;

	double increaseFireDamage;
	double increaseWaterDamage;
	double increaseEarthDamage;
	double increaseAirDamage;
	double increaseDarkDamage;
	double increaseLightDamage;

	double FireProtection;
	double WaterProtection;
	double EarthProtection;
	double AirProtection;
	double DarkProtection;
	double LightProtection;

	double armor;
};

