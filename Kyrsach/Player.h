#pragma once
#include "Entity.h"
class Player :public Entity
{
public:
	Player(b2World *world,double x, double y);
	void Control();
	void Update(double time)override;
	void SetCamera(sf::View &camera);

	sf::Vector2f getPosition();
	void Draw(sf::RenderWindow &window)override;

private:
	
};

