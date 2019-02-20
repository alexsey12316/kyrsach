#include "Entity.h"



Entity::Entity(double x,double y)
{
	this->x = x;
	this->y = y;
	isAlive = 1;
	isHurt = 0;
	animation.setPosition(x, y);
	FallSpeed = 150;
}

Entity::Entity(double x, double y, double width, double height):Entity(x,y)
{
	this->width = width;
	this->height = height;
	rect.setSize(sf::Vector2f(width, height));

}

void Entity::Draw(sf::RenderWindow & window)
{
	animation.draw(window);
}

void Entity::setHealth(double health)
{
	this->health = health;
}

void Entity::setMaxHealth(double MaxHealth)
{
	this->MaxHealth = MaxHealth;
	if (MaxHealth < health)
		health = MaxHealth;

}

void Entity::setObjects(std::vector<Object>& vec)
{
	this->Objects = vec;
}





