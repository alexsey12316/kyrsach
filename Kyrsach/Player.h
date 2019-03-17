#pragma once

#include "Entity.h"
#include<list>


//class Entity;
class Player :public Entity
{
public:
	Player(b2World *world,double x, double y);
	void Control();
	void Update(double time)override;
	void SetCamera(sf::View &camera);
	b2World* GetWorldPointer();
	Direction GetDirection();
	void SetMagic(std::list<Magic*> &magic);
	void Ability();
	void Draw(sf::RenderWindow &window)override;
	sf::Vector2f getPosition();

private:
	bool isCasting;
	std::list<Magic*> *magic;
	double mana;
	double MaxMana;
	double ManaPerTime;
	double ManaTimer;

};

