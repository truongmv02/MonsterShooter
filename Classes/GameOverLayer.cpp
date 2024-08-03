#include "GameOverLayer.h"
#include "MainMenuScene.h"
#include "GameManager.h"
#include "Definitions.h"
#include "SoundManager.h"

GameOverLayer* GameOverLayer::create(const Color4B color)
{
	GameOverLayer* layer = new (std::nothrow) GameOverLayer();
	if (layer && layer->initWithColor(color))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool GameOverLayer::initWithColor(const Color4B color) {
	if (!LayerColor::initWithColor(color)) {
		return false;
	}

	auto background = Sprite::create(PATH_IMAGE_UI + "dialog1.png");
	background->setPosition(VISIBLE_SIZE / 2);
	this->addChild(background);

	auto backItem = MenuItemImage::create(PATH_IMAGE_UI + "backbtn.png",
		PATH_IMAGE_UI + "backbtn_selected.png", CC_CALLBACK_0(GameOverLayer::goToMainMenuCallback, this));
	auto gameOverImg = Sprite::create(PATH_IMAGE_UI + "gameover.png");
	auto bgSize = background->getContentSize();
	gameOverImg->setPosition(bgSize.width / 2, bgSize.height - gameOverImg->getContentSize().height - 20);
	background->addChild(gameOverImg);
	auto menu = Menu::create(backItem, nullptr);
	menu->setPosition(bgSize / 2);
	background->addChild(menu);
	this->setVisible(false);
	return true;
}

void GameOverLayer::goToMainMenuCallback() {
	SoundManager::getInstance()->stopBackgroundMusic();
	auto scene = MainMenuScene::create();
	Director::getInstance()->replaceScene(scene);
}