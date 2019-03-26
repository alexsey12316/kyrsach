#pragma once
#include<SFML/Audio.hpp>
#include "RayCastObject.h"
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
	virtual void behavior(double);
	virtual void SetTarget(Player *target);
	bool isDelete();
	void Draw(sf::RenderWindow &window)override;

protected:
	behaviorType Benavior;
	sf::RectangleShape scope;
	b2Body *LeftDamageArea;
	b2Body *RightDamageArea;
	sf::RectangleShape LeftDebugDamageArea;
	sf::RectangleShape RightDebugDamageArea;
	bool isAttack;
	bool Delete;
	double AttackTimer;
	double currentAttackTimer;
	double Damage;
	Player *target;
	sf::SoundBuffer buffer;
	sf::Sound soundEffect;
	RayCastObject RayCast;
	double MovementTimer;
	double currentMovementTimer;
};

class EnemyKnight_2:public Enemy
{
public:
	EnemyKnight_2(b2World *world, double x, double y);
	~EnemyKnight_2();
	void Update(double time)override;

private:
};

