#pragma once
#include "Entity.h"
class Player :public Entity
{
public:
	Player(double x, double y);
	void Control();
	void Update(double time)override;

	sf::Vector2f getPosition();
	void Draw(sf::RenderWindow &window);

private:

};

