#pragma once

#include "cocos2d.h"
#include "Character.h"
#include "Weapon.h"

class Mage : public Character
{
public:
	Mage() { this->name = "Mage"; }
	bool init();
	void initBody() override;
	void update(float dt) override;
	void attack(Vec2 dir) override;
public:
	CREATE_FUNC(Mage);
protected:
};
