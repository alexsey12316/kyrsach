#pragma once
#include"Animation.h"
#include"Box2D/Box2D.h"
#include<SFML/Audio.hpp>
#include"Player.h"

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
};


class  FireBall:public Magic
{
public:
	 FireBall(Player &player);
	~FireBall();
	void UpDate(double time)override;
	static bool isReady();
	static void check(double time);

private:
	static double RollTime;
	static bool isAvailable;
	static double RollBack;
};

