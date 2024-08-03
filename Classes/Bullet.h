

#pragma once
#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;
class Bullet : public Entity
{
public:
	Bullet();
	virtual bool initWithName(std::string name);
	virtual bool initWithSprite(Sprite* sprite, std::string name);
	virtual void initBody();
	virtual void update(float dt);
public:
	CREATE_WITH_NAME_FUNC(Bullet);
	CREATE_WITH_SPRITE_FUNC(Bullet);
	CC_SYNTHESIZE(float, dame, Dame);
	CC_SYNTHESIZE(float, flyingSpeed, FlyingSpeed);
	CC_SYNTHESIZE(Vec2, pointStart, PointStart);
	CC_SYNTHESIZE(float, distanceFly, DistanceFly);
};

