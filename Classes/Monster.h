#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "Definitions.h"
#include "IMonster.h"
USING_NS_CC;
using namespace ui;

class Monster :public IMonster {
public:
	Monster();
	virtual bool initWithName(std::string name);
	virtual	bool initWithSprite(Sprite* sprite, std::string name);
	virtual void initBody();
	virtual void initHpBar();
	void createBullet(Vec2 dir);
	virtual void update(float dt);
	virtual	void attack();
	virtual void remove();
public:
	CREATE_WITH_NAME_FUNC(Monster);
	CREATE_WITH_SPRITE_FUNC(Monster);
};

