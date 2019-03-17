#include "Entity.h"

#include "Magic.h"


Entity::~Entity()
{
	world->DestroyBody(body);
}

Entity::Entity(double x,double y)
{
	this->x = x;
	this->y = y;
	isAlive = 1;
	isHurt = 0;
	increaseAirDamage = 0;
	increaseFireDamage = 0;
	increaseWaterDamage = 0;
	increaseEarthDamage = 0;
	increaseLightDamage = 0;
	increaseDarkDamage = 0;
	
	LightProtection = 0;
	DarkProtection = 0;
	FireProtection = 0;
	WaterProtection = 0;
	EarthProtection = 0;
	AirProtection = 0;
}

Entity::Entity(double x, double y, double width, double height):Entity(x,y)
{
	this->width = width;
	this->height = height;
	rect.setSize(sf::Vector2f(width, height));

}



void Entity::Draw(sf::RenderWindow & window)
{
#ifdef RECT
	window.draw(rect);
#endif // RECT

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


void Entity::SetDamage(Magic * magic)
{
	isHurt = 1;
	switch (magic->GetElement())
	{
	case Magic::Element::Fire:
		if (FireProtection <= 100)
		{
			Magic::Element el;
			el = Magic::Element::Fire;
			double Damage = magic->GetDamage(el);
			health -= Damage - this->FireProtection / 100 * Damage;
		}
		break;
	case Magic::Element::Water:
		if (WaterProtection <= 100)
		{
			Magic::Element el;
			el = Magic::Element::Water;
			double Damage = magic->GetDamage(el);
			health -= Damage - this->WaterProtection / 100 * Damage;
		}
		break;
	case Magic::Element::Earth:
		if (EarthProtection <= 100)
		{
			Magic::Element el;
			el = Magic::Element::Earth;
			double Damage = magic->GetDamage(el);
			health -= Damage - this->EarthProtection / 100 * Damage;
		}
		break;
	case Magic::Element::Air:
		if (AirProtection <= 100)
		{
			Magic::Element el;
			el = Magic::Element::Air;
			double Damage = magic->GetDamage(el);
			health -= Damage - this->AirProtection / 100 * Damage;
		}
		break;
	case Magic::Element::Light:
		if (LightProtection <= 100)
		{
			Magic::Element el;
			el = Magic::Element::Light;
			double Damage = magic->GetDamage(el);
			health -= Damage - this->LightProtection / 100 * Damage;
		}
		break;
	case Magic::Element::Dark:
		if (DarkProtection <= 100)
		{
			Magic::Element el;
			el = Magic::Element::Dark;
			double Damage = magic->GetDamage(el);
			health -= Damage - this->DarkProtection / 100 * Damage;
		}
		break;
	}

}



