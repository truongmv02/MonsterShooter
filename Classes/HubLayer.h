#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "StateBoard.h"
#include "PauseLayer.h"
#include "GameOverLayer.h"
#include "VictoryLayer.h"

USING_NS_CC;
using namespace ui;
class HubLayer :public Layer
{
public:
	bool init();
	CREATE_FUNC(HubLayer);
	CC_SYNTHESIZE(Button*, pauseBtn, PauseBtn);
	CC_SYNTHESIZE(StateBoard*, stateBoard, StateBoard);
	CC_SYNTHESIZE(PauseLayer*, pauseLayer, PauseLayer);
	CC_SYNTHESIZE(GameOverLayer*, gameOverLayer, GameOverLayer);
	CC_SYNTHESIZE(VictoryLayer*, victoryLayer, VictoryLayer);

};
