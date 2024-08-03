#include "LoadingScene.h"
#include "MainMenuScene.h"
#include"GameScene.h"
#include "Definitions.h"
#include "Utility.h"

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	_total = 7;
	_count = 0;
	Utility::UI::addCenterBackgroundToScene(PATH_IMAGE_UI + "background.png", this);
	sliderLoading = Slider::create();
	sliderLoading->loadBarTexture(PATH_IMAGE_UI + "loading_bg.png");
	sliderLoading->loadProgressBarTexture(PATH_IMAGE_UI + "loading_progress.png");
	sliderLoading->setEnabled(false);
	sliderLoading->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 5));
	sliderLoading->setPercent(0);
	this->addChild(sliderLoading);
	loadResources();
	this->scheduleUpdate();
	return true;
}


void LoadingScene::loadResources() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DATA_PLIST + "Mage.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DATA_PLIST + "Explosion1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DATA_PLIST + "Rock.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DATA_PLIST + "Bat.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DATA_PLIST + "Deathspirit.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DATA_PLIST + "Gosth.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DATA_PLIST + "Ariman.plist");
	Director::getInstance()->getTextureCache()->addImageAsync(PATH_IMAGE_CHARACTER + "Mage.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(PATH_IMAGE_EFFECT + "Explosion1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(PATH_IMAGE_MONSTER + "Rock.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(PATH_IMAGE_MONSTER + "Bat.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(PATH_IMAGE_MONSTER + "Deathspirit.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(PATH_IMAGE_MONSTER + "Ariman.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync(PATH_IMAGE_MONSTER + "Gosth.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack(Texture2D* texture) {
	_count++;
	float percent = (float)_count / (float)_total * 100;
	sliderLoading->setPercent(percent);

}

void LoadingScene::update(float dt) {
	if (_count >= _total) {
		this->unscheduleUpdate();
		auto scene = MainMenuScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
}