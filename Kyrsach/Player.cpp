#include "Player.h"

#define RECT

Player::Player(b2World *world, double x, double y) :Entity(x, y)
{
	height = 100;
	width = 60;

	b2BodyDef definition;
	definition.type = b2BodyType::b2_dynamicBody;
	definition.position.Set((x + width / 2) / SCALE, (height / 2 + y) / SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(width / 2 / SCALE, height / 2 / SCALE);
	b2FixtureDef fixture;
	fixture.friction = 0;
	fixture.shape = &shape;
	fixture.density = 1;
	body = world->CreateBody(&definition);
	body->CreateFixture(&fixture);

	health = 100;
	MaxHealth = 100;
	animation.setFrameSize(height, height);
	animation.setImage("character/player.png");
	animation.setSize(10, 6);
	animation.setPosition(x - 20, height);
	OnGround = 0;
	direction = Direction::Stay_Right;
	
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(x, y));
	rect.setFillColor(sf::Color::Green);
	Speed = 4;
	JumpTime = currentJumpTime = 0.7;
	EnableJump = 0;

}

void Player::Control()
{
	if (isHurt&&isAlive)
	{

	


	}
	else if (isAlive&&OnGround)
	{
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W) && EnableJump)
		{
			direction = Direction::Jump_Left;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W) && EnableJump)
		{
			direction = Direction::Jump_Right;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			direction = Direction::Left;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			direction = Direction::Right;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && EnableJump)
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
}

void Player::Update(double time)
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
			body->SetLinearVelocity(b2Vec2(Speed, -Speed));
			animation.setAnimation(4, Animation::AnimationType::once);


		}
		else
		{
			EnableJump = 0;
			if (OnGround)
				direction = Stay_Right;

		}
		break;
	case  Direction::Jump_Left:
		if (currentJumpTime > 0)
		{
			currentJumpTime -= time;

			OnGround = 0;
			body->SetLinearVelocity(b2Vec2(-Speed, -Speed));
			animation.setAnimation(5, Animation::AnimationType::once);

		}
		else
		{
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
			body->SetLinearVelocity(b2Vec2(0, -Speed));
			if (animation.GetCurrentRow() % 2 != 0)
				animation.setAnimation(5, Animation::AnimationType::once);
			else
				animation.setAnimation(4, Animation::AnimationType::once);

		}
		else
		{
			EnableJump = 0;
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
			animation.setAnimation(9, Animation::AnimationType::once);
		}
		else if (direction == Direction::Right || direction == Direction::Jump_Right || direction == Direction::Stay_Right)
		{
			animation.setAnimation(8, Animation::AnimationType::once);
		}
	}
	else if (isHurt)
	{

		if (direction == Direction::Left || direction == Direction::Jump_Left || direction == Direction::Stay_Left)
		{
			isHurt = !animation.setAnimation(7, Animation::AnimationType::once);

		}
		else if (direction == Direction::Right || direction == Direction::Jump_Right || direction == Direction::Stay_Right)
		{
			isHurt = !animation.setAnimation(6, Animation::AnimationType::once);
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

			currentJumpTime += time;
		}
	}

	body->SetFixedRotation(1);
	x = body->GetPosition().x*SCALE;
	y = body->GetPosition().y * SCALE;
	x -= width / 2;
	y -= height / 2;
	animation.Animate(4 * time);
	animation.setPosition(x - 20, y);
	rect.setPosition(sf::Vector2f(x, y));
}
void Player::SetCamera(sf::View & camera)
{
	if (!OnGround)
	{
		if (camera.getCenter().y < y + height)
		{
			sf::Vector2f vec = camera.getCenter();
			if (vec.y < y) {
				vec.y += body->GetLinearVelocity().y / 2;
				camera.setCenter(x, vec.y);

			}
			else
			{
				camera.setCenter(x, camera.getCenter().y);

			}
		}
		else
		{
			camera.setCenter(x, camera.getCenter().y);
		}
	}
	else
	{
		if (camera.getCenter().y < y - 3 || camera.getCenter().y > y + 3)
		{
			sf::Vector2f vec = camera.getCenter();
			if (vec.y < y) {
				vec.y += 1;
				camera.setCenter(x, vec.y);
			}
			else
			{
				vec.y -= 1;
				camera.setCenter(x, vec.y);

			}

		}
		else
		{

			camera.setCenter(x, y);
		}

	}
}
sf::Vector2f Player::getPosition()
{
	return sf::Vector2f(this->x, this->y);
}

void Player::Draw(sf::RenderWindow & window)
{
#ifdef RECT
	window.draw(rect);
#endif // RECT

	animation.draw(window);
}
