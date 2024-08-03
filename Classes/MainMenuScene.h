#pragma once
#include "cocos2d.h"
USING_NS_CC;

class MainMenuScene :public Scene
{
public:
	bool init();
	void goToGameScene();
	bool onTouchBegan(Touch* touch, Event* event);
	CREATE_FUNC(MainMenuScene);

};
