#include <string>
#include "Character.h"
#include "Utility.h"
#include "InputHandler.h"
#include "GameManager.h"

Character::Character() {
	weapon = nullptr;
	mp = 400;
	mpMax = 400;
	speed = 400;
	isAttack = false;
}

void Character::initWeapon(std::string name) {
	weapon = Weapon::createWithSprite(Sprite::create(PATH_IMAGE_WEAPON + name + ".png"));
	weapon->setPosition(Vec2(this->getContentSize().width / 2 + 10, this->getContentSize().height / 4));
	this->addChild(weapon, 1);
	weapon->setDirection(dir);
}

void Character::move(Vec2 dir) {
	if (hp <= 0 || dirMove == dir) {
		return;
	}
	dirMove = dir;
	auto action = Utility::CCUtility::getAnimate(name + "/run", 0.05, -1);
	if (this->getActionByTag(TAG_ACTION_IDLE)) {
		this->stopActionByTag(TAG_ACTION_IDLE);
	}
	if (this->getActionByTag(TAG_ACTION_MOVE)) {
		this->stopActionByTag(TAG_ACTION_MOVE);
	}
	action->setTag(TAG_ACTION_MOVE);
	this->runAction(action);
}

void Character::idle() {
	if (hp <= 0 || this->getActionByTag(TAG_ACTION_IDLE) != NULL) {
		return;
	}
	this->initWithSpriteFrameName(name + "/idle1.png");
	auto action = Utility::CCUtility::getAnimate(
		name + "/idle", 0.1, -1);
	action->setTag(TAG_ACTION_IDLE);
	if (this->getActionByTag(TAG_ACTION_MOVE)) {
		this->stopActionByTag(TAG_ACTION_MOVE);
	}
	this->runAction(action);
}

void Character::dead() {
	dirMove = Vec2::ZERO;
	this->stopAllActions();
	this->initWithSpriteFrameName(name + "/death.png");
	this->setFlippedX(dir.x <= 0);
	if (weapon) {
		this->weapon->setVisible(false);
	}
}

void Character::update(float dt) {
	EntityLife::update(dt);
	if (weapon && InputHandler::getInstance()->isMouseDown(InputHandler::BUTTON_LEFT)) {
		setDirectionX((weapon->getDirection().x <= 0.0f) ? DIR_LEFT : DIR_RIGHT);
	}
	else if (dirMove.x || dirMove.y && !InputHandler::getInstance()->isMouseDown(InputHandler::BUTTON_LEFT))
	{
		if (weapon && (dirMove.x && dir.x != dirMove.x)) {
			weapon->setDirectionX(-weapon->getDirection().x);
		}
		Utility::CCUtility::setDir(dirMove, dir);
	}
}

void Character::updateEventKeyBoard(float dt) {
	InputHandler* instance = InputHandler::getInstance();
#define keyCode (int)EventKeyboard::KeyCode

#define checkKey instance->isKeyPress

	Vec2 dir;
	if (checkKey(keyCode::KEY_A) || checkKey(keyCode::KEY_LEFT_ARROW)) {
		dir.x = DIR_LEFT;
	}
	else if (checkKey(keyCode::KEY_D) || checkKey(keyCode::KEY_RIGHT_ARROW)) {
		dir.x = DIR_RIGHT;

	}
	else if (checkKey(keyCode::KEY_W) || checkKey(keyCode::KEY_UP_ARROW)) {
		dir.y = DIR_UP;
	}
	else if (checkKey(keyCode::KEY_S) || checkKey(keyCode::KEY_DOWN_ARROW)) {
		dir.y = DIR_DOWN;
	}

	if (dir.x || dir.y) {
		this->move(dir);
	}
	else {
		this->setDirMove(Vec2::ZERO);
		this->idle();
	}
}