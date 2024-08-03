#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"

class Weapon : public Entity
{
public:
	Weapon();
	virtual bool initWithName(std::string name);
	virtual bool initWithSprite(Sprite* sprite, std::string name);
	void update(float dt);
	void attack(Vec2 dir);
	void createBullet(Vec2 dir);
public:
	CREATE_WITH_NAME_FUNC(Weapon);
	CREATE_WITH_SPRITE_FUNC(Weapon);
	CC_SYNTHESIZE(std::string, bulletName, BulletName);
	CC_SYNTHESIZE(int, dame, Dame);
	CC_SYNTHESIZE(float, gapTime, GapTime);
	CC_SYNTHESIZE(int, enegryCost, EnegryCost);
};

