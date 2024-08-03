

#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "Definitions.h"
#include "EntityLife.h"
USING_NS_CC;
using namespace ui;

class Pillar : public EntityLife
{
public:
	Pillar();
	virtual bool initWithName(std::string name);
	virtual bool initWithSprite(Sprite* sprite, std::string name);
	void initHpBar();
	void initBody();
	virtual void update(float dt);

public:
	CREATE_WITH_NAME_FUNC(Pillar);
	CREATE_WITH_SPRITE_FUNC(Pillar);
	
protected:
	Slider* hpBar;
};

