#include "Magic.h"

//Basic class
Magic::Magic()
{
}


Magic::~Magic()
{
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


// class fire ball
FireBall::FireBall(Player &player)
{
	RollBack = RollTime;
	isAvailable = 0;
	this->x = player.getPosition().x;
	this->y = player.getPosition().y;
	this->world = player.GetWorldPointer();
	animation.setImage("magic/fire/fireball/fireball.png");
	animation.setFrameSize(100, 60);
	animation.setSize(4, 6);
	buffer.loadFromFile("magic/fire/fireball/burn.ogg");
	soundEffect.setBuffer(buffer);
	soundEffect.play();
	//soundEffect.setLoop(1);


	b2BodyDef definition;

	if (player.GetDirection() == Entity::Direction::Stay_Left)
	{
		direction = Left;
		definition.position.Set((x - 50) / SCALE, (y + 70) / SCALE);
	}
	else if (player.GetDirection() == Entity::Direction::Stay_Right)
	{
		direction = Right;
		definition.position.Set((x + 106) / SCALE, (y + 70) / SCALE);
	}
	rect.setSize(sf::Vector2f(100, 60));
	rect.setPosition(sf::Vector2f(x, y));
	rect.setFillColor(sf::Color::Green);
	definition.type = b2BodyType::b2_dynamicBody;

	b2PolygonShape shape;
	b2FixtureDef DefShape;
	shape.SetAsBox(45 / SCALE, 25 / SCALE);
	DefShape.isSensor = 1;
	DefShape.shape = &shape;
	body = world->CreateBody(&definition);
	body->CreateFixture(&DefShape);
	body->SetGravityScale(0);


	initialization = 1;
	destroy = 0;

	speed = 10;
	Timer = 15;
}

FireBall::~FireBall()
{
	soundEffect.stop();
}

void FireBall::UpDate(double time)
{
	this->x = body->GetPosition().x*SCALE;
	this->y = body->GetPosition().y*SCALE;
	rect.setPosition(x - 50, y - 30);
	animation.setPosition(x - 50, y - 30);
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
			}
			else
			{
				initialization = !animation.setAnimation(2, Animation::AnimationType::once);
			}
		}
		else
		{
			if (direction == Left)
			{
				animation.setAnimation(1, Animation::AnimationType::loop);
				body->SetLinearVelocity(b2Vec2(-speed, 0));
			}
			else
			{
				body->SetLinearVelocity(b2Vec2(speed, 0));
				animation.setAnimation(0, Animation::AnimationType::loop);
			}

			if(!destroy)
			for (auto i = body->GetContactList(); i != nullptr; i = i->next)
				if (body->GetContactList()->contact->IsTouching())
					destroy = 1;
		}
	}

	initialization ? animation.Animate(6 * time) : animation.Animate(8 * time);
}

bool FireBall::isReady()
{
	return isAvailable;
}

void FireBall::check(double time)
{
	if (!isAvailable)
	{
		if (RollBack > 0)
			RollBack -= time;
		else
			isAvailable = 1;
	}

}
// static variables
double FireBall::RollTime = 5;
bool FireBall::isAvailable = 1;
double FireBall::RollBack;
