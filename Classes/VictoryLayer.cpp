#include "VictoryLayer.h"
#include "MainMenuScene.h"
#include "GameManager.h"
#include "Definitions.h"
#include "SoundManager.h"

VictoryLayer* VictoryLayer::create(const Color4B color)
{
	VictoryLayer* layer = new (std::nothrow) VictoryLayer();
	if (layer && layer->initWithColor(color))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool VictoryLayer::initWithColor(const Color4B color) {
	if (!LayerColor::initWithColor(color)) {
		return false;
	}

	auto background = Sprite::create(PATH_IMAGE_UI + "dialog1.png");
	background->setPosition(VISIBLE_SIZE / 2);
	this->addChild(background);

	auto backItem = MenuItemImage::create(PATH_IMAGE_UI + "backbtn.png",
		PATH_IMAGE_UI + "backbtn_selected.png", CC_CALLBACK_0(VictoryLayer::goToMainMenuCallback, this));
	auto winImg = Sprite::create(PATH_IMAGE_UI + "win.png");
	auto bgSize = background->getContentSize();
	winImg->setPosition(bgSize.width / 2, bgSize.height - winImg->getContentSize().height - 20);
	background->addChild(winImg);
	auto menu = Menu::create(backItem, nullptr);
	menu->setPosition(bgSize / 2);
	background->addChild(menu);
	this->setVisible(false);
	return true;
}

void VictoryLayer::goToMainMenuCallback() {
	SoundManager::getInstance()->stopBackgroundMusic();
	auto scene = MainMenuScene::create();
	Director::getInstance()->replaceScene(scene);
}