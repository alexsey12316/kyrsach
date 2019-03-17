#include "Magic.h"

#include "Player.h"



Magic::Magic()
{
}


Magic::~Magic()
{
	if (body != nullptr)
		world->DestroyBody(body);
}

void Magic::Draw(sf::RenderWindow & window)
{
#ifdef DEBUG
	window.draw(rect);
#endif // DEBUG
	animation.draw(window);

}

bool Magic::isDestroy()
{
	return destroy;
}

Magic::Element Magic::GetElement()
{
	return element;
}

double Magic::GetDamage(Element & el)
{
	switch (el)
	{
	case Element::Fire:
		return FireDamage;

	case Element::Water:
		return WaterDamage;

	case Element::Earth:
		return EarthDamage;

	case Element::Air:
		return AirDamage;

	case Element::Light:
		return LightDamage;

	case Element::Dark:
		return DarkDamage;


	}
}

void Magic::CheckCollision()
{
	if (!destroy)
		for (auto i = body->GetContactList(); i != nullptr; i = i->next)
			if (body->GetContactList()->contact->IsTouching())
				if (body->GetContactList()->contact->GetFixtureA()->GetBody()->GetUserData() != body->GetUserData())
				{
					destroy = 1;

					Entity*value = static_cast<Entity*>(body->GetContactList()->contact->GetFixtureA()->GetBody()->GetUserData());
					if (value != nullptr)
					{
						value->SetDamage(this);
					}
				}
}

////////////////////////////////////////////////////////////////////////////////////////////
// class fire ball
FireBall::FireBall(Player &player)
{

	this->x = player.getPosition().x;
	this->y = player.getPosition().y;
	this->world = player.GetWorldPointer();
	animation.setImage("magic/fire/fireball/fireball.png");
	animation.setFrameSize(80, 48);
	animation.setSize(4, 6);
	buffer.loadFromFile("magic/fire/fireball/burn.ogg");
	soundEffect.setBuffer(buffer);
	soundEffect.play();

	b2BodyDef definition;

	if (player.GetDirection() == Entity::Direction::Stay_Left)
	{
		direction = Left;
		definition.position.Set((x - 70) / SCALE, (y + 70) / SCALE);
	}
	else if (player.GetDirection() == Entity::Direction::Stay_Right)
	{
		direction = Right;
		definition.position.Set((x + 126) / SCALE, (y + 70) / SCALE);
	}
	rect.setSize(sf::Vector2f(80, 48));
	rect.setPosition(sf::Vector2f(x, y));
	rect.setFillColor(sf::Color::Green);
	definition.type = b2BodyType::b2_dynamicBody;

	b2CircleShape circle;
	circle.m_radius = 15 / SCALE;
	b2FixtureDef DefShape;
	DefShape.isSensor = 1;
	DefShape.shape = &circle;
	body = world->CreateBody(&definition);
	body->CreateFixture(&DefShape);
	body->SetGravityScale(0);
	body->SetUserData(&player);

	initialization = 1;
	destroy = 0;

	speed = 10;
	Timer = 15;
	FireDamage = 30;
	element = Fire;
}

FireBall::~FireBall()
{
	soundEffect.stop();
}

void FireBall::UpDate(double time)
{
	this->x = body->GetPosition().x*SCALE;
	this->y = body->GetPosition().y*SCALE;

	if (Timer < 0) {
		destroy = 1;
	}
	else
	{
		Timer -= time;
		body->SetAngularVelocity(0);
		if (initialization)
		{
			if (direction == Left)
			{
				initialization = !animation.setAnimation(3, Animation::AnimationType::once);
				rect.setPosition(x - 20, y - 24);
				animation.setPosition(x - 20, y - 24);
			}
			else
			{
				initialization = !animation.setAnimation(2, Animation::AnimationType::once);
				rect.setPosition(x - 60, y - 24);
				animation.setPosition(x - 60, y - 24);
			}
		}
		else
		{
			if (direction == Left)
			{
				animation.setAnimation(1, Animation::AnimationType::loop);
				body->SetLinearVelocity(b2Vec2(-speed, 0));
				rect.setPosition(x - 20, y - 24);
				animation.setPosition(x - 20, y - 24);
			}
			else
			{
				body->SetLinearVelocity(b2Vec2(speed, 0));
				animation.setAnimation(0, Animation::AnimationType::loop);
				rect.setPosition(x - 60, y - 24);
				animation.setPosition(x - 60, y - 24);
			}
			CheckCollision();
			
		}
	}

	initialization ? animation.Animate(6 * time) : animation.Animate(8 * time);
}


double FireBall::Consumption()
{
	return consumption;
}
// static variables
double FireBall::consumption = 10;