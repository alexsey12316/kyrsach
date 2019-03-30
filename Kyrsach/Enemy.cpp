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
	if (LeftDamageArea != nullptr)
		world->DestroyBody(LeftDamageArea);
	if (RightDamageArea != nullptr)
		world->DestroyBody(RightDamageArea);
}

void Enemy::behavior(double time)
{
	switch (Benavior)
	{
	case Enemy::debug:
	{
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentAttackTimer == AttackTimer)
			{
				if (direction == Direction::Stay_Left || direction == Direction::Stay_Right)
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
	}
	case Enemy::calm:

		if (currentMovementTimer < 0)
		{
			switch (direction)
			{
			case Direction::Stay_Left:
				direction = Direction::Right;

				break;
			case Direction::Right:
				direction = Direction::Stay_Right;

				break;

			case Direction::Stay_Right:
				direction = Direction::Left;
				break;
			case Direction::Left:
				direction = Direction::Stay_Left;

				break;
			}
			currentMovementTimer = MovementTimer;
		}
		else
		{
			currentMovementTimer -= time;
			if (body->GetLinearVelocity().x < 0.1)
			{
				if (direction == Direction::Right)
				{
					direction = Direction::Stay_Right;
				}
				else if (direction == Direction::Left)
				{
					direction == Direction::Stay_Left;
				}
			}
		}

		RayCast.SetPosition(b2Vec2((x + width / 2) / SCALE, (y + height / 4) / SCALE));

		if (direction == Direction::Left || direction == Direction::Stay_Left || direction == Direction::Jump_Left)
			RayCast.SetSector(210, 330);
		else if (direction == Direction::Right || direction == Direction::Stay_Right || direction == Direction::Jump_Right)
			RayCast.SetSector(30, 150);

		RayCast.upDate(this);

		break;
	case Enemy::Agressive:
		if (isAlive && !isHurt && !isAttack)
		{
			sf::Vector2f position = target->getPosition();
			if (OnGround)
			{
				if (position.x - 100 > x)
				{
					direction = Direction::Right;
				}
				else if (position.x + 100 < x)
				{
					direction = Direction::Left;

				}
			}
			if (position.y < y&&body->GetLinearVelocity().x < 0.1||(body->GetLinearVelocity().x==0&&!(direction==Direction::Stay_Left|| direction == Direction::Stay_Right)))
			{
				if (position.x > x)
				{
					if (target->isOnGround() && EnableJump&&OnGround)
						direction = Direction::Jump_Right;

				}
				else
				{
					if (target->isOnGround() && EnableJump&&OnGround)
					{
						direction = Direction::Jump_Left;
					}

				}

			}
			if (OnGround&&currentAttackTimer == AttackTimer)
			{
				if (position.y  > y-30 && position.y < y+30)
				{

					if (position.x + 70 > x&&position.x < x)
					{
						direction = Direction::Stay_Left;
						isAttack = 1;
					}
					else if (position.x - 100 < x&&position.x > x)
					{
						direction = Direction::Stay_Right;
						isAttack = 1;
					}
				}
			}
		}
		break;
	}




}

void Enemy::SetTarget(Player * target)
{
	this->target = target;
	Benavior = behaviorType::Agressive;
}

bool Enemy::isDelete()
{
	return Delete;
}

void Enemy::Draw(sf::RenderWindow & window)
{
#ifdef DEBUG
	window.draw(rect);
	window.draw(LeftDebugDamageArea);
	window.draw(RightDebugDamageArea);
	RayCast.Draw(window);
#endif // DEBUG
	animation.draw(window);
}



///////////////////////////////////////////////////////
//Knight 2
EnemyKnight_2::EnemyKnight_2(b2World *world, double x, double y) :Enemy(x, y)
{
	this->world = world;
	RayCast.SetWorld(world);
	RayCast.SetRayLength(25);
	RayCast.SetStep(5);
	width = 70;
	height = 110;
	b2BodyDef definition;
	definition.type = b2BodyType::b2_dynamicBody;
	definition.position.Set((x + width / 2) / SCALE, (y + height / 2) / SCALE);
	RayCast.SetPosition(definition.position);
	RayCast.SetSector(0, 180);
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


	definition.position.Set((x + width - 200 / 2) / SCALE, (y + height / 2) / SCALE);

	shape.SetAsBox(50 / 2 / SCALE, 50 / 2 / SCALE);
	fixture.shape = &shape;
	fixture.isSensor = 1;


	LeftDamageArea = this->world->CreateBody(&definition);
	LeftDamageArea->CreateFixture(&fixture);
	LeftDamageArea->SetFixedRotation(1);
	LeftDamageArea->SetGravityScale(0);
	LeftDamageArea->SetUserData(this);


	definition.position.Set((x + width + 60 / 2) / SCALE, (y + height / 2) / SCALE);

	RightDamageArea = this->world->CreateBody(&definition);
	RightDamageArea->CreateFixture(&fixture);
	RightDamageArea->SetFixedRotation(1);
	RightDamageArea->SetGravityScale(0);
	RightDamageArea->SetUserData(this);
	///For Debug
	LeftDebugDamageArea.setFillColor(sf::Color::Red);
	RightDebugDamageArea.setFillColor(sf::Color::Red);
	LeftDebugDamageArea.setSize(sf::Vector2f(50, 50));
	RightDebugDamageArea.setSize(sf::Vector2f(50, 50));
	//debugDamageArea.setPosition(sf::Vector2f(50, 50));


	Benavior = Enemy::behaviorType::calm;


	this->buffer.loadFromFile("character/enemy_knight_2.ogg");
	soundEffect.setBuffer(buffer);
	soundEffect.setVolume(70);
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color::Blue);

	animation.setImage("character/enemy_knight_2.png");
	animation.setFrameSize(160, 130);
	animation.setSize(12, 7);
	animation.setPosition(x - 40, y - 20);

	Speed = 4;
	powerJump = 6;
	JumpTime = currentJumpTime = 0.7;
	health = MaxHealth = 100;
	AttackTimer = currentAttackTimer = 4;
	Damage = 40;
	currentMovementTimer = MovementTimer = 2;
}

EnemyKnight_2::~EnemyKnight_2()
{
}

void EnemyKnight_2::Update(double time)
{
	b2Vec2 temp = body->GetLinearVelocity();
	if (body->GetPosition().y > RightDamageArea->GetPosition().y)
		temp.y += 0.15;
	RightDamageArea->SetLinearVelocity(temp);
	LeftDamageArea->SetLinearVelocity(temp);

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

		this->body->SetLinearVelocity(b2Vec2(0,body->GetLinearVelocity().y));
		if (direction == Direction::Left || direction == Direction::Jump_Left || direction == Direction::Stay_Left)
		{
			isHurt = !animation.setAnimation(9, Animation::AnimationType::once);
			direction = Direction::Stay_Left;

		}
		else if (direction == Direction::Right || direction == Direction::Jump_Right || direction == Direction::Stay_Right)
		{
			isHurt = !animation.setAnimation(8, Animation::AnimationType::once);
			direction = Direction::Stay_Right;
		}

	}
	else if (isAttack)
	{
		if (direction == Direction::Stay_Left)
			isAttack = !animation.setAnimation(7, Animation::AnimationType::once);
		else if (direction == Direction::Stay_Right)
			isAttack = !animation.setAnimation(6, Animation::AnimationType::once);

		if (currentAttackTimer == AttackTimer)
		{
			currentAttackTimer = 0;
		}
		if (!isAttack)
		{
			soundEffect.play();

			if (direction == Direction::Stay_Left)
			{
				for (auto i = LeftDamageArea->GetContactList(); i != nullptr; i = i->next)
					if (LeftDamageArea->GetContactList()->contact->IsTouching())
						if (LeftDamageArea->GetContactList()->contact->GetFixtureA()->GetBody()->GetUserData() == target)
						{
							target->SetDamage(Damage);
							break;

						}
			}
			else if (direction == Direction::Stay_Right)
			{
				for (auto i = RightDamageArea->GetContactList(); i != nullptr; i = i->next)
					if (RightDamageArea->GetContactList()->contact->IsTouching())
						if (RightDamageArea->GetContactList()->contact->GetFixtureA()->GetBody()->GetUserData() == target)
						{
							target->SetDamage(Damage);
							break;

						}
			}
		}

	}
	else
	{
		switch (this->direction)
		{
		case Direction::Stay_Left:
			if (OnGround)
			{
				body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
			}
			animation.setAnimation(1, Animation::AnimationType::loop);

			break;
		case Direction::Stay_Right:
			if (OnGround)
			{
				body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
			}
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
				animation.setAnimation(4, Animation::AnimationType::once, 0);
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
				animation.setAnimation(5, Animation::AnimationType::once, 0);
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
	if (currentAttackTimer < AttackTimer)
		currentAttackTimer += time;
	else if (currentAttackTimer > AttackTimer)
		currentAttackTimer = AttackTimer;

	x = body->GetPosition().x * SCALE;
	y = body->GetPosition().y * SCALE;


	//damageArea->S
	LeftDebugDamageArea.setPosition(LeftDamageArea->GetPosition().x*SCALE - 25, LeftDamageArea->GetPosition().y*SCALE - 25);
	RightDebugDamageArea.setPosition(RightDamageArea->GetPosition().x*SCALE - 25, RightDamageArea->GetPosition().y*SCALE - 25);
	x -= width / 2;
	y -= height / 2;
	animation.Animate(10 * time);
	animation.setPosition(x - 40, y - 20);
	rect.setPosition(sf::Vector2f(x, y));
}
