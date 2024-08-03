#pragma once

#include "cocos2d.h"
#include "EntityLife.h"
#include "Weapon.h"

class Character : public EntityLife
{
public:
	Character();
	virtual void initBody() = 0;
	virtual void update(float dt);
	virtual void move(Vec2 dir);
	virtual void attack(Vec2 dir) = 0;
	virtual void idle();
	virtual void dead();
	virtual void initWeapon(std::string weaponName);
	void updateEventKeyBoard(float dt);
public:
	CC_SYNTHESIZE(unsigned int, mp, Mp);
	CC_SYNTHESIZE(unsigned int, mpMax, MpMax);
	CC_SYNTHESIZE(Weapon*, weapon, Weapon);
protected:
};
