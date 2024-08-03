#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class LoadingScene : public Scene
{
public:
	bool init();
	void loadResources();
	void loadingCallBack(Texture2D* texture);
	void update(float dt);
	CREATE_FUNC(LoadingScene);
private:
	int _total;
	int _count;
	Slider* sliderLoading;

};
