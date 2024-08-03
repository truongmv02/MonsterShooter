#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "Definitions.h"
#include "EntityLife.h"

USING_NS_CC;
using namespace ui;

class IMonster : public EntityLife
{
public:
	IMonster() { isDead = false; }
	virtual void initBody() = 0;
	virtual void initHpBar() = 0;
	virtual void createBullet(Vec2 dir) = 0;
	virtual	void attack() = 0;
	virtual void remove() = 0;
public:
	CC_SYNTHESIZE(float, attackRange, AttackRange);
	CC_SYNTHESIZE(float, dame, Dame);
	CC_SYNTHESIZE(float, attackSpeed, AttackSpeed);
	CC_SYNTHESIZE(bool, isDead, IsDead);
protected:
	Slider* hpBar;
	bool isAttack = false;
};

