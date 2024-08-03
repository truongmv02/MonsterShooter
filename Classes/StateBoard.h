

#pragma once
#include "cocos2d.h"
#include "Definitions.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "Character.h"
USING_NS_CC;
using namespace ui;
class StateBoard : public Node
{
public:
	virtual bool init();
	void initHpBar();
	void initMpBar();
	void update(float dt);
	void setHpBar();
	void setMpBar();
	CREATE_FUNC(StateBoard);
protected:
	Sprite* stateBoard;
	LoadingBar* hpBar;
	LoadingBar* mpBar;
	LabelAtlas* labelHp;
	LabelAtlas* labelMp;
};

