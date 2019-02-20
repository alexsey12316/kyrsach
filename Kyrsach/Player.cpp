#include "Player.h"

//#define RECT

Player::Player(double x, double y) :Entity(x, y)
{
	health = 100;
	MaxHealth = 100;
	Speed = 100;
	animation.setFrameSize(160, 160);
	animation.setImage("character/player.png");
	animation.setSize(10, 6);
	animation.setPosition(x - 30, y);
	OnGround = 0;


	rect.setPosition(sf::Vector2f(x, y));
	rect.setSize(sf::Vector2f(100, 160));
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
			if (direction == Direction::Left || direction == Direction::Jump_Left)
			{
				direction = Direction::Stay_Left;
				animation.setAnimation(1, Animation::AnimationType::loop);

			}
			else if (direction == Direction::Right || direction == Direction::Jump_Right)
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
	animation.Animate(4*time);
	
	switch (this->direction)
	{
	case  Direction::Stay_Left:
		if (!this->OnGround)
		{
			y += FallSpeed * time;
		}
		break;
	case  Direction::Stay_Right:
		if (!this->OnGround)
		{
			y += FallSpeed * time;

		}
		
		break;
	case  Direction::Left:
		if (this->OnGround)
		{
			x -= Speed * time;
		}
		else
		{
			y += FallSpeed * time;
		}
		break;
	case  Direction::Right:
		if (this->OnGround)
		{
			x += Speed * time;

		}
		else
		{
			y += FallSpeed * time;
		}
		break;
	}

	CheckCollision();
	animation.setPosition(x - 30, y);
	rect.setPosition(sf::Vector2f(x, y));
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

void Player::CheckCollision()
{
	bool flag = 0;
	for (int i=0; i < Objects.size(); i++)
	{
		if (rect.getGlobalBounds().intersects(Objects[i].rect))
		{
			if (Objects[i].name == "solid")
			{
				flag = 1;
				OnGround = 1;
				std::cout << "here\n";
			}
			
		}
	
	}
	if (!flag)
		OnGround = 0;
}

