#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include"Box2D/Box2D.h"
#include"Animation.h"

//#define DEBUG 

class Player;

class Magic
{
public:
	enum Element {
		Fire,Water,Earth,Air,Light,Dark
	};
	enum Direction {
		Left,Right
	};
	Magic();
	virtual ~Magic();
	virtual void UpDate(double time) = 0;
	virtual void Draw(sf::RenderWindow &window);
	virtual bool isDestroy();
	Element GetElement();
	double GetDamage(Element &el);

protected:
	Direction direction;
	sf::SoundBuffer buffer;
	sf::Sound soundEffect;
	sf::RectangleShape rect;
	Animation animation;
	double FireDamage;
	double WaterDamage;
	double EarthDamage;
	double AirDamage;
	double DarkDamage;
	double LightDamage;
	double Timer;
	b2Body *body;
	b2World *world;
	double x, y;
	double speed;
	bool initialization;
	bool destroy;
	Element element;

	void CheckCollision();
};


class  FireBall:public Magic
{
public:
	 FireBall(Player &player);
	~FireBall();
	void UpDate(double time)override;
	static double Consumption();
	
private:
	
	static double consumption;
};

