#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class GameOverLayer :public LayerColor
{
public:
	static GameOverLayer* create(const Color4B color);
	bool initWithColor(const Color4B color);
	void goToMainMenuCallback();
};
