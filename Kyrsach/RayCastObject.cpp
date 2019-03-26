#include "RayCastObject.h"
#include "Enemy.h"





RayCastObject::RayCastObject()
{
	step = 1;
	SectorBegin = 0;
	SectorEnd = 45;
	rayLength = 1;
	currentRayAngle = 0;

}

RayCastObject::~RayCastObject()
{
}

void RayCastObject::SetWorld(b2World * world)
{
	this->world = world;
}

void RayCastObject::SetPosition(b2Vec2 point)
{
	this->point = point;
	pixel.x = point.x*SCALE;
	pixel.y = point.y*SCALE;
}

void RayCastObject::upDate(Enemy *enemy)
{

	for (double i = SectorBegin; i < SectorEnd; i += step)
	{
		currentRayAngle = i * DEGTORAD;
		b2Vec2 p2 = point + rayLength * b2Vec2(sinf(currentRayAngle), cosf(currentRayAngle));
		Player *temp = nullptr;
		temp = static_cast<Player *>(RayBuild(p2));
		if (temp != nullptr)
		{
				//std::cout << "gatcha" << std::endl;
			enemy->SetTarget(temp);
		}

	}
}

void RayCastObject::Draw(sf::RenderWindow & window)
{
	for (size_t i = 0; i < coords.size(); i++)
	{
		sf::VertexArray a(sf::PrimitiveType::Lines, 2);
		a[0].position = pixel;
		a[1] = coords[i];
		window.draw(a);
	}
	coords.clear();
}


void* RayCastObject::RayBuild(b2Vec2 end)
{
	b2RayCastInput input;

	input.p1 = this->point;
	input.p2 = end;
	input.maxFraction = 1;
	void *temp=nullptr;
	//check every fixture of every body to find closest
	float closestFraction = 1; //start with end of line as p2
	b2Vec2 intersectionNormal(0, 0);
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {

		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
			if (!f->IsSensor())
			{

				b2RayCastOutput output;
				if (!f->RayCast(&output, input, 0))
					continue;
				if (output.fraction < closestFraction) {
					temp = b->GetUserData();
					closestFraction = output.fraction;
					intersectionNormal = output.normal;
				}
			}
		}
	}

	b2Vec2 intersectionPoint = point + closestFraction * (end - point);
	sf::Vertex p;


	p.position.x = intersectionPoint.x*SCALE;
	p.position.y = intersectionPoint.y*SCALE;
	coords.push_back(p);
	return temp;

}

void RayCastObject::SetSector(double begin, double end)
{
	this->SectorBegin = begin;
	this->SectorEnd = end;
}

void RayCastObject::SetStep(double step)
{
	this->step = step;
}

void RayCastObject::SetRayLength(double length)
{
	rayLength = length;
}
