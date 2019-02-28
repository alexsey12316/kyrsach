#include "Animation.h"



Animation::Animation()
{
	this->currentFrame = 0;
	this->currentRow = 0;
	progress = 0;
}

Animation::Animation(sf::String &str, int width, int height) :Animation()
{
	this->str = str;
	this->width = width;
	this->height = height;
	image.loadFromFile(this->str);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	this->rows = image.getSize().y / height;
	this->columns = image.getSize().x / width;

}

Animation::Animation(const char * str, int width, int height) :Animation()
{
	this->str = str;
	this->width = width;
	this->height = height;
	image.loadFromFile(this->str);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	this->rows = image.getSize().y / height;
	this->columns = image.getSize().x / width;
}

void Animation::setSize(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
}

void Animation::setFrameSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Animation::setImage(sf::String & str)
{
	this->str = str;
	this->image.loadFromFile(str);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));


}

void Animation::setImage(const char * str)
{
	this->str = str;
	this->image.loadFromFile(str);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
}

void Animation::setImage(sf::Image & image)
{
	this->image = image;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
}


void Animation::draw(sf::RenderWindow & window)
{
	window.draw(this->sprite);
}

void Animation::setPosition(double x, double y)
{
	this->x = x;
	this->y = y;
	sprite.setPosition(x, y);
}

void Animation::Animate(double time)
{
	switch (animationType)
	{
	case AnimationType::loop:
		progress += time;
		currentFrame = int(progress);
		sprite.setTextureRect(sf::IntRect(width*currentFrame, height*currentRow, width, height));
		if (progress > columns - 0.5)
			progress = 0;
		break;
	case AnimationType::once:
		if (progress < columns - 0.5)
			progress += time;

		currentFrame = int(progress);
		sprite.setTextureRect(sf::IntRect(width*currentFrame, height*currentRow, width, height));
		break;
	}



}

bool Animation::setAnimation(int currentRow, AnimationType type)
{
	this->currentRow = currentRow;
	this->animationType = type;

	if (currentFrame == columns-1)
		return 0;
	else
		return 1;


}

int Animation::GetCurrentRow()
{
	return currentRow;
}



