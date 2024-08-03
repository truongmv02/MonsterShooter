#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "Definitions.h"
#include "Monster.h"
#include "GameManager.h"

USING_NS_CC;
using namespace ui;

class Boss : public Monster
{
public:
	Boss();
	virtual bool initWithName(std::string name);
	virtual	bool initWithSprite(Sprite* sprite, std::string name);
	virtual void initHpBar();
	virtual void update(float dt);
	virtual	void attack(float dt);
public:
	CREATE_WITH_NAME_FUNC(Boss);
	CREATE_WITH_SPRITE_FUNC(Boss);
};

