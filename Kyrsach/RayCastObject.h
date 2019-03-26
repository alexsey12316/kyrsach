#pragma once
#include "Player.h"

class Enemy;
class RayCastObject 
{
public:
	RayCastObject();
	~RayCastObject();
	void SetWorld(b2World *world);
	void SetPosition(b2Vec2);
	void upDate(Enemy *enemy);
	void Draw(sf::RenderWindow &window);
	void* RayBuild( b2Vec2 end);
	void SetSector(double begin, double end);
	void SetStep(double step);
	void SetRayLength(double length);
private:
	b2Vec2 point;
	sf::Vector2f pixel;
	std::vector<sf::Vertex> coords;

	double rayLength;
	double SectorBegin;
	double SectorEnd;
	double step;

	double currentRayAngle;
	b2World *world;



	const double SCALE = 30;
	const double DEGTORAD = 0.0174532925199432957;
	const double RADTODEG = 57.295779513082320876;
};

