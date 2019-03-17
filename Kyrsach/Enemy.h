#pragma once
#include "Player.h"
#define DEBUG

class Enemy :
	public Entity
{
public:
	enum behaviorType {
		debug,calm,Agressive
	};
	Enemy(double x, double y);
	virtual ~Enemy();
	virtual void behavior();
	bool isDelete();
	void Draw(sf::RenderWindow &window)override;

protected:
	behaviorType Benavior;
	sf::RectangleShape scope;
	bool isAttack;
	bool Delete;
	Player *target;

};

class EnemyKnight_2:public Enemy
{
public:
	EnemyKnight_2(b2World *world, double x, double y);
	~EnemyKnight_2();
	void Update(double time)override;

private:
};

