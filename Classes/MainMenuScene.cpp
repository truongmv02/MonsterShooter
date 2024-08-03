#include "MainMenuScene.h"
#include "GameScene.h"
#include "Utility.h"
#include "GameManager.h"
#include "SoundManager.h"

bool MainMenuScene::init() {
	if (!Scene::init()) {
		return false;
	}
	Utility::UI::addCenterBackgroundToScene(PATH_IMAGE_UI + "background.png", this);
	auto menuItem = MenuItemImage::create(PATH_IMAGE_UI + "play.png",
		PATH_IMAGE_UI + "play_selected.png", CC_CALLBACK_0(MainMenuScene::goToGameScene, this));
	auto menu = Menu::create(menuItem, nullptr);
	this->addChild(menu);
	SoundManager::getInstance()->playBackgroundMusic(PATH_SOUND + "StartGame.mp3");
	auto lis = EventListenerMouse::create();
	return true;
}

void MainMenuScene::goToGameScene() {
	SoundManager::getInstance()->stopBackgroundMusic();
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(scene);
}
