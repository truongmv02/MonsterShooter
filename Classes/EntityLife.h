

#pragma once
#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;
class EntityLife : public Entity
{
public:
	EntityLife();
	virtual bool initWithName(std::string name);
	virtual bool initWithSprite(Sprite* sprite, std::string name);
	virtual void update(float dt);
	virtual void move();
public:
	CREATE_WITH_NAME_FUNC(EntityLife);
	CREATE_WITH_SPRITE_FUNC(EntityLife);
	CC_SYNTHESIZE(unsigned int, hp, Hp);
	CC_SYNTHESIZE(Vec2, dirMove, DirMove);
	CC_SYNTHESIZE(unsigned int, hpMax, HpMax);
	CC_SYNTHESIZE(bool, isAttack, IsAttack);
	CC_SYNTHESIZE(unsigned int, speed, Speed);
protected:
	TMXLayer* metaLayer;
};

