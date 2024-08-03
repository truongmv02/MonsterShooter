#include "HubLayer.h"
#include "MainMenuScene.h"
#include "GameManager.h"
#include "PauseLayer.h"
#include "GameOverLayer.h"

bool HubLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	stateBoard = StateBoard::create();
	this->addChild(stateBoard, 10);

	pauseBtn = Button::create(PATH_IMAGE_UI + "pausebtn.png", PATH_IMAGE_UI + "pausebtn_selected.png");
	pauseBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{

		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			GameManager::getInstance()->pauseGame();
			break;
		}
		});
	pauseBtn->setPosition(Vec2(VISIBLE_SIZE_WIDTH - pauseBtn->getContentSize().width / 1.5,
		VISIBLE_SIZE_HEIGHT - pauseBtn->getContentSize().height / 1.5));
	this->addChild(pauseBtn, 10);

	pauseLayer = PauseLayer::create(Color4B(0, 0, 0, 200));
	pauseLayer->setPosition(Vec2::ZERO);
	this->addChild(pauseLayer, 100, "PauseLayer");

	gameOverLayer = GameOverLayer::create(Color4B(0, 0, 0, 200));
	gameOverLayer->setPosition(Vec2::ZERO);
	this->addChild(gameOverLayer, 100, "GameOverLayer");

	victoryLayer = VictoryLayer::create(Color4B(0, 0, 0, 200));
	victoryLayer->setPosition(Vec2::ZERO);
	this->addChild(victoryLayer, 100, "GameOverLayer");
	return true;
}