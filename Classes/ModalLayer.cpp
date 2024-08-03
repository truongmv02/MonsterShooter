#include "PauseLayer.h"
#include "MainMenuScene.h"
#include "GameManager.h"
#include "Definitions.h"

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

	background = Sprite::create(PATH_IMAGE_UI + "dialog.png");
	background->setPosition(VISIBLE_SIZE / 2);
	this->addChild(background);

	auto resumeItem = MenuItemImage::create(PATH_IMAGE_UI + "startbtn.png",
		PATH_IMAGE_UI + "startbtn_selected", CC_CALLBACK_0(PauseLayer::resumeGameCallback, this));
	auto backItem = MenuItemImage::create(PATH_IMAGE_UI + "backbtn.png",
		PATH_IMAGE_UI + "backbtn_selected.png", CC_CALLBACK_0(PauseLayer::goToMainMenuCallback, this));

	menu = Menu::create(resumeItem, backItem, nullptr);
	menu->alignItemsHorizontallyWithPadding(20);
	this->addChild(menu);

	return true;
}

void PauseLayer::resumeGameCallback() {
	this->setVisible(false);
	GameManager::getInstance()->resumeGame();
}

void PauseLayer::goToMainMenuCallback() {
	auto scene = MainMenuScene::create();
	Director::getInstance()->replaceScene(scene);
}