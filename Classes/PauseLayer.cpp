#include "PauseLayer.h"
#include "MainMenuScene.h"
#include "GameManager.h"
#include "Definitions.h"
#include "SoundManager.h"

PauseLayer* PauseLayer::create(const Color4B color)
{
	PauseLayer* layer = new (std::nothrow) PauseLayer();
	if (layer && layer->initWithColor(color))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool PauseLayer::initWithColor(const Color4B color) {
	if (!LayerColor::initWithColor(color)) {
		return false;
	}

	auto	background = Sprite::create(PATH_IMAGE_UI + "dialog.png");
	background->setPosition(VISIBLE_SIZE / 2);
	this->addChild(background);

	auto resumeItem = MenuItemImage::create(PATH_IMAGE_UI + "startbtn.png",
		PATH_IMAGE_UI + "startbtn_selected.png", [&](Ref* sender) {
			this->setVisible(false);
			GameManager::getInstance()->resumeGame();
		});

	auto backItem = MenuItemImage::create(PATH_IMAGE_UI + "backbtn.png",
		PATH_IMAGE_UI + "backbtn_selected.png", [&](Ref* sender) {
			SoundManager::getInstance()->stopBackgroundMusic();
			auto scene = MainMenuScene::create();
			Director::getInstance()->replaceScene(scene);
		});

	auto soundOn = MenuItemImage::create(PATH_IMAGE_UI + "sound_on.png", PATH_IMAGE_UI + "sound_on.png");
	auto soundOf = MenuItemImage::create(PATH_IMAGE_UI + "sound_off.png", PATH_IMAGE_UI + "sound_off.png");

	auto itemToggle = MenuItemToggle::createWithCallback([&](Ref* sender) {
		SoundManager::getInstance()->setPlay(!SoundManager::getInstance()->getPlay());
		}, soundOn, soundOf, nullptr);

	if (!SoundManager::getInstance()->getPlay()) {
		itemToggle->setSelectedIndex(1);
	}

	auto menu = Menu::create(itemToggle, resumeItem, backItem, nullptr);
	menu->alignItemsHorizontallyWithPadding(background->getContentSize().width / 9);
	this->addChild(menu);
	this->setVisible(false);
	return true;
}

void PauseLayer::resumeGameCallback() {
	this->setVisible(false);
	GameManager::getInstance()->resumeGame();
}

void PauseLayer::goToMainMenuCallback() {
	SoundManager::getInstance()->stopBackgroundMusic();
	auto scene = MainMenuScene::create();
	Director::getInstance()->replaceScene(scene);
}