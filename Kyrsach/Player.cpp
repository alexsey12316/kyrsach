#include "Player.h"

#define RECT

Player::Player(double x, double y) :Entity(x, y)
{
	health = 100;
	MaxHealth = 100;
	Speed = 100;
	animation.setFrameSize(160, 160);
	animation.setImage("character/player.png");
	animation.setSize(10, 6);
	animation.setPosition(x - 70, y - height);
	OnGround = 0;
	direction = Direction::Stay_Right;
	height = 160;
	width = 100;

	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(x, y));
	rect.setOrigin(width / 2, height);
	rect.setFillColor(sf::Color::Green);
}

void Player::Control()
{
	if (isHurt)
	{

		if (direction == Direction::Left)
		{
			direction = Direction::Stay_Left;
			isHurt = animation.setAnimation(7, Animation::AnimationType::once);

		}
		else if (direction == Direction::Right)
		{
			direction = Direction::Stay_Right;
			isHurt = animation.setAnimation(6, Animation::AnimationType::once);


		}


	}
	else if (isAlive&&OnGround)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			direction = Direction::Jump_Left;
			animation.setAnimation(5, Animation::AnimationType::once);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			direction = Direction::Jump_Right;
			animation.setAnimation(4, Animation::AnimationType::once);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			direction = Direction::Left;
			animation.setAnimation(3, Animation::AnimationType::loop);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			direction = Direction::Right;
			animation.setAnimation(2, Animation::AnimationType::loop);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (direction == Direction::Left || direction == Direction::Stay_Left)
			{
				direction = Direction::Jump;
				animation.setAnimation(5, Animation::AnimationType::once);

			}
			else if (direction == Direction::Right || direction == Direction::Stay_Right)
			{
				direction = Direction::Jump;
				animation.setAnimation(4, Animation::AnimationType::once);

			}
		}
		else
		{
			if (direction == Direction::Left || direction == Direction::Jump_Left || (direction == Direction::Jump&&animation.GetCurrentRow() % 2 != 0))
			{
				direction = Direction::Stay_Left;
				animation.setAnimation(1, Animation::AnimationType::loop);

			}
			else if (direction == Direction::Right || direction == Direction::Jump_Right || (direction == Direction::Jump&&animation.GetCurrentRow() % 2 == 0))
			{
				direction = Direction::Stay_Right;
				animation.setAnimation(0, Animation::AnimationType::loop);

			}
		}
	}
	else if (!isAlive)
	{
		if (direction == Direction::Left || direction == Direction::Jump_Left)
		{
			direction = Direction::Stay_Left;
			animation.setAnimation(9, Animation::AnimationType::once);

		}
		else if (direction == Direction::Right || direction == Direction::Jump_Right)
		{
			direction = Direction::Stay_Right;
			animation.setAnimation(8, Animation::AnimationType::once);

		}
	}
}

void Player::Update(double time)
{


	/*switch (this->direction)
	{

	case  Direction::Left:
		x -= Speed * time;

		break;
	case  Direction::Right:
		x += Speed * time;

		break;
	case  Direction::Jump_Right:
		x += Speed * time;
		JumpTime -= time;
		if (JumpTime > 0)
		{
			currentJumpPower -= 100 * time;
			y -= currentJumpPower * time;
		}
		else
		{
			currentJumpPower += 100 * time;
			y += currentJumpPower * time;
		}
		break;
	case  Direction::Jump_Left:
		x -= Speed * time;
		JumpTime -= time;
		if (JumpTime > 0)
		{
			currentJumpPower -= 100 * time;
			y -= currentJumpPower * time;
		}
		else
		{
			currentJumpPower += 100 * time;
			y += currentJumpPower * time;

		}
		break;
	case  Direction::Jump:
		JumpTime -= time;
		if (JumpTime > 0)
		{
			currentJumpPower -= 100 * time;
			y -= currentJumpPower * time;
		}
		else
		{
			currentJumpPower += 100 * time;
			y += currentJumpPower * time;

		}
		break;

	}*/
	
	animation.Animate(4 * time);
	animation.setPosition(x - 75, y - height);
	rect.setPosition(sf::Vector2f(x, y));
}
void Player::SetCamera(sf::View & camera)
{
	if (direction == Direction::Jump || direction == Direction::Jump_Left || direction == Direction::Jump_Right)
	{
		camera.setCenter(x, camera.getCenter().y);
	}
	else
	{
		camera.setCenter(x, y - camera.getSize().y / 4);

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
