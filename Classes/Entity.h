

#pragma once
#include "cocos2d.h"
#include "Definitions.h"
USING_NS_CC;
class Entity : public Sprite
{
public:
	Entity();
	virtual bool initWithName(std::string name);
	virtual bool initWithSprite(Sprite* sprite, std::string name);

	inline void setDirectionX(float x) { dir.x = x; }
	inline void setDirectionY(float y) { dir.y = y; }
	virtual void update(float dt);

public:
	CREATE_WITH_NAME_FUNC(Entity);
	CREATE_WITH_SPRITE_FUNC(Entity);
	CC_SYNTHESIZE(Vec2, dir, Direction);
	CC_SYNTHESIZE(std::string, name, EName);
protected:
};

