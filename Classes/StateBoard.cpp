#include "StateBoard.h"
#include "GameManager.h"

bool StateBoard::init() {
	stateBoard = Sprite::create(PATH_IMAGE_UI + "state_bar.png");
	stateBoard->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	stateBoard->setPosition(Vec2(0, VISIBLE_SIZE_HEIGHT));
	initHpBar();
	initMpBar();
	this->addChild(stateBoard);
	this->scheduleUpdate();
	return true;
}

void StateBoard::update(float dt) {
	setHpBar();
	setMpBar();
}

void StateBoard::initHpBar() {
	auto stateBoardSize = stateBoard->getContentSize();
	hpBar = LoadingBar::create(PATH_IMAGE_UI + "hp_bar.png");
	hpBar->setDirection(LoadingBar::Direction::LEFT);
	hpBar->setAnchorPoint(Vec2(0, 0));
	hpBar->setPosition(Vec2(stateBoardSize.width / 2.7, stateBoardSize.height / 1.55));
	stateBoard->addChild(hpBar, -1);

	labelHp = LabelAtlas::
		create(NUMBER_STRING, PATH_IMAGE_NUMBER + "number_white.png", 10, 16, '0');

	labelHp->setAnchorPoint(Vec2(0, 0.25));
	labelHp->setPosition(Vec2(50, labelHp->getContentSize().height / 2));
	hpBar->addChild(labelHp);
	setHpBar();
}

void StateBoard::initMpBar() {

	auto stateBoardSize = stateBoard->getContentSize();
	mpBar = LoadingBar::create(PATH_IMAGE_UI + "mp_bar.png");
	mpBar->setDirection(LoadingBar::Direction::LEFT);
	mpBar->setAnchorPoint(Vec2(0, 0));
	mpBar->setPosition(Vec2(stateBoardSize.width / 2.7, stateBoardSize.height / 3));
	stateBoard->addChild(mpBar, -1);

	labelMp = LabelAtlas::
		create(NUMBER_STRING, PATH_IMAGE_NUMBER + "number_white.png", 10, 16, '0');

	labelMp->setAnchorPoint(Vec2(0, 0.25));
	labelMp->setPosition(Vec2(50, labelMp->getContentSize().height / 2));
	mpBar->addChild(labelMp);
	setMpBar();
}


void StateBoard::setMpBar() {
	auto character = GameManager::getInstance()->getCharacter();
	auto percent = character->getMp() / (float)character->getMpMax() * 100;
	mpBar->setPercent(percent);
	labelMp->setString(std::to_string(character->getMp()));
}

void StateBoard::setHpBar() {
	auto character = GameManager::getInstance()->getCharacter();
	auto percent = character->getHp() / (float)character->getHpMax() * 100;
	hpBar->setPercent(percent);
	labelHp->setString(std::to_string(character->getHp()));
}