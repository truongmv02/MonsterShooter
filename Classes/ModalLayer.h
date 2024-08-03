#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class PauseLayer :public LayerColor
{
public:
	static PauseLayer* create(const Color4B color);
	bool initWithColor(const Color4B color);
protected:
	Sprite* background;
	Menu* menu;
};
