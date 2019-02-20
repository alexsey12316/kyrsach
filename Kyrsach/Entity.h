#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include"Animation.h"
#include"Level.h"
class Entity
{
public:
	enum Direction
	{
		Left,Right,Stay_Left,Stay_Right,Jump,Jump_Left,Jump_Right
	};
	Entity(double x,double y);
	Entity(double x,double y,double width,double height);
	virtual void Update(double time) = 0;
	virtual void Draw(sf::RenderWindow &window);
	virtual void setHealth(double health);
	virtual void setMaxHealth(double MaxHealth);
	virtual void setObjects(std::vector<Object> &vec);
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
	std::vector<Object> Objects;
	double Speed;
	bool OnGround;
	double FallSpeed;
};

