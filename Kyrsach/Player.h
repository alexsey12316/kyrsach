#pragma once

#ifndef PLAYER_H
#define PLAYER_H


#include "Entity.h"
#include<list>
#include"Magic.h"


class Magic;
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

	sf::Vector2f getPosition();
	void Draw(sf::RenderWindow &window)override;

private:
	double powerJump;
	std::list<Magic*> *magic;
};

#endif // !PLAYER_H
