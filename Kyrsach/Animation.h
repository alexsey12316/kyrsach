#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

class Animation
{
public:
	enum AnimationType {
		loop, once
	};

	Animation();
	Animation(sf::String &str, int width, int height);
	Animation(const char*str, int width, int height);
	void setSize(int rows, int columns);
	void setFrameSize(int width, int height);
	void setImage(sf::String &str);
	void setImage(const char*str);
	void setImage(sf::Image &image);
	void draw(sf::RenderWindow & window);
	void setPosition(double x, double y);
	void Animate(double time);
	bool setAnimation(int currentRow, AnimationType type,bool restart=1);
	int GetCurrentRow();

private:
	double progress;
	double x, y;
	int width, height;
	int rows, columns;
	int currentFrame;
	int currentRow;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String str;
	AnimationType animationType;
};

