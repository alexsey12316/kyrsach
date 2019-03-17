#include "Enemy.h"

#include "Magic.h"

///////////////////////////////////////////////////////////
//Basic class 

Enemy::Enemy(double x, double y) :Entity(x, y)
{
	Delete = 0;
	OnGround = 0;
	if (rand() % 2 == 0)
		direction = Direction::Stay_Left;
	else
		direction = Direction::Stay_Right;
}


Enemy::~Enemy()
{
}

void Enemy::behavior()
{
	switch (Benavior)
	{
	case Enemy::debug:
		if (isHurt&&isAlive || isAttack && isAlive)
		{
		}
		else if (isAlive && !OnGround)
		{
			if (direction == Direction::Jump_Left || direction == Direction::Jump_Right)
			{
				direction = Direction::Jump;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (direction == Direction::Jump)
				{
					direction = Direction::Jump_Left;
				}



			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (direction == Direction::Jump)
				{
					direction = Direction::Jump_Right;
				}

			}
		}
		else if (isAlive&&OnGround)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (direction == Direction::Stay_Left || direction == Direction::Right || direction == Direction::Stay_Right || direction == Direction::Left)
					isAttack = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && EnableJump)
			{
				direction = Direction::Jump_Left;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && EnableJump)
			{
				direction = Direction::Jump_Right;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				direction = Direction::Left;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				direction = Direction::Right;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && EnableJump)
			{
				if (direction == Direction::Left || direction == Direction::Stay_Left)
				{
					direction = Direction::Jump;

				}
				else if (direction == Direction::Right || direction == Direction::Stay_Right)
				{
					direction = Direction::Jump;

				}
			}
			else
			{
				if (direction == Direction::Left || direction == Direction::Jump_Left || (direction == Direction::Jump&&animation.GetCurrentRow() % 2 != 0))
				{
					direction = Direction::Stay_Left;

				}
				else if (direction == Direction::Right || direction == Direction::Jump_Right || (direction == Direction::Jump&&animation.GetCurrentRow() % 2 == 0))
				{
					direction = Direction::Stay_Right;

				}
			}
		}
		else if (!isAlive)
		{
			if (direction == Direction::Left || direction == Direction::Jump_Left)
			{
				direction = Direction::Stay_Left;

			}
			else if (direction == Direction::Right || direction == Direction::Jump_Right)
			{
				direction = Direction::Stay_Right;

			}
		}
		break;
	case Enemy::calm:
		break;
	case Enemy::Agressive:
		break;

	}
}

bool Enemy::isDelete()
{
	return Delete;
}

void Enemy::Draw(sf::RenderWindow & window)
{
#ifdef DEBUG
	window.draw(rect);
#endif // DEBUG
	animation.draw(window);
}



///////////////////////////////////////////////////////
//Knight 2
EnemyKnight_2::EnemyKnight_2(b2World *world, double x, double y) :Enemy(x, y)
{
	this->world = world;
	width = 70;
	height = 110;
	b2BodyDef definition;
	definition.type = b2BodyType::b2_dynamicBody;
	definition.position.Set((x + width / 2) / SCALE, (y + height / 2) / SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(width / 2 / SCALE, height / 2 / SCALE);
	b2FixtureDef fixture;
	fixture.friction = 0;
	fixture.shape = &shape;
	fixture.density = 1;

	body = this->world->CreateBody(&definition);
	body->CreateFixture(&fixture);
	body->SetFixedRotation(1);
	body->SetUserData(this);


	Benavior = Enemy::behaviorType::debug;



	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color::Blue);

	animation.setImage("character/enemy_knight_2.png");
	animation.setFrameSize(160, 130);
	animation.setSize(12, 7);
	animation.setPosition(x - 40, y - 20);

	Speed = 4;
	powerJump = 5;
	JumpTime = currentJumpTime = 0.7;
	health = MaxHealth = 100;

}

EnemyKnight_2::~EnemyKnight_2()
{
}

void EnemyKnight_2::Update(double time)
{

	switch (this->direction)
	{
	case Direction::Stay_Left:
		if (OnGround)
			body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
		animation.setAnimation(1, Animation::AnimationType::loop);

		break;
	case Direction::Stay_Right:
		if (OnGround)
			body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
		animation.setAnimation(0, Animation::AnimationType::loop);


		break;
	case  Direction::Left:
		if (OnGround)
		{
			body->SetLinearVelocity(b2Vec2(-Speed, body->GetLinearVelocity().y));
			animation.setAnimation(3, Animation::AnimationType::loop);

		}
		break;
	case  Direction::Right:
		if (OnGround)
		{
			body->SetLinearVelocity(b2Vec2(Speed, body->GetLinearVelocity().y));
			animation.setAnimation(2, Animation::AnimationType::loop);

		}
		break;
	case  Direction::Jump_Right:
		if (currentJumpTime > 0)
		{
			currentJumpTime -= time;

			OnGround = 0;
			body->SetLinearVelocity(b2Vec2(Speed, -powerJump));
			animation.setAnimation(4, Animation::AnimationType::once);


		}
		else
		{
			animation.setAnimation(4, Animation::AnimationType::once);
			EnableJump = 0;
			body->SetLinearVelocity(b2Vec2(Speed, body->GetLinearVelocity().y));
			if (OnGround)
				direction = Stay_Right;

		}
		break;
	case  Direction::Jump_Left:
		if (currentJumpTime > 0)
		{
			currentJumpTime -= time;

			OnGround = 0;
			body->SetLinearVelocity(b2Vec2(-Speed, -powerJump));
			animation.setAnimation(5, Animation::AnimationType::once);

		}
		else
		{
			animation.setAnimation(5, Animation::AnimationType::once);
			body->SetLinearVelocity(b2Vec2(-Speed, body->GetLinearVelocity().y));
			EnableJump = 0;
			if (OnGround)
				direction = Stay_Left;
		}
		break;
	case  Direction::Jump:
		if (currentJumpTime > 0)
		{
			currentJumpTime -= time;
			OnGround = 0;
			body->SetLinearVelocity(b2Vec2(0, -powerJump));
			if (animation.GetCurrentRow() % 2 != 0)
				animation.setAnimation(5, Animation::AnimationType::once);
			else
				animation.setAnimation(4, Animation::AnimationType::once);

		}
		else
		{
			EnableJump = 0;
			body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));

			if (OnGround)
			{
				if (animation.GetCurrentRow() % 2 != 0)
					direction = Stay_Left;
				else
					direction = Stay_Right;
			}
		}
		break;

	}
	if (!isAlive)
	{
		if (direction == Direction::Left || direction == Direction::Jump_Left || direction == Direction::Stay_Left)
		{
			Delete = !animation.setAnimation(11, Animation::AnimationType::once);
		}
		else if (direction == Direction::Right || direction == Direction::Jump_Right || direction == Direction::Stay_Right)
		{
			Delete = !animation.setAnimation(10, Animation::AnimationType::once);
		}
	}
	else if (isHurt)
	{

		if (direction == Direction::Left || direction == Direction::Jump_Left || direction == Direction::Stay_Left)
		{
			isHurt = !animation.setAnimation(9, Animation::AnimationType::once);

		}
		else if (direction == Direction::Right || direction == Direction::Jump_Right || direction == Direction::Stay_Right)
		{
			isHurt = !animation.setAnimation(8, Animation::AnimationType::once);
		}

	}
	else if (isAttack)
	{
		if (direction == Direction::Stay_Left)
			isAttack = !animation.setAnimation(7, Animation::AnimationType::once);
		else if (direction == Direction::Stay_Right)
			isAttack = !animation.setAnimation(6, Animation::AnimationType::once);

	}
	if (body->GetLinearVelocity().y == 0)
	{
		OnGround = 1;
		if (currentJumpTime >= JumpTime)
		{
			currentJumpTime = JumpTime;
			EnableJump = 1;
		}
		else
		{

			currentJumpTime += 2 * time;
		}
	}
	if (this->health < 0)
	{
		health = 0;
		isAlive = 0;
	}

	//std::cout << body->GetLinearVelocity().x << "\t" << body->GetLinearVelocity().y << "\t"<< OnGround << "\n";

	x = body->GetPosition().x*SCALE;
	y = body->GetPosition().y * SCALE;
	x -= width / 2;
	y -= height / 2;
	animation.Animate(4 * time);
	animation.setPosition(x - 40, y - 20);
	rect.setPosition(sf::Vector2f(x, y));
}
