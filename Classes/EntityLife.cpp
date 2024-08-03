#include "EntityLife.h"
#include "GameManager.h"
#include "Utility.h"


EntityLife::EntityLife() {
	speed = 0;
	hp = 500;
	hpMax = 500;
	dirMove = Vec2::ZERO;
	isAttack = false;
}

bool EntityLife::initWithName(std::string name) {
	if (!Entity::initWithName(name)) {
		return false;
	}
	return true;
}

bool EntityLife::initWithSprite(Sprite* sprite, std::string name) {
	if (!Entity::initWithSprite(sprite, name)) {
		return false;
	}
	return true;
}


void EntityLife::move() {
	auto newPos = this->getPosition();
	auto size = this->getContentSize();
	auto tileSize = GameManager::getInstance()->getTileMap()->getTileSize();

	newPos.y -= size.height / 3;
	if (dirMove.x == DIR_LEFT) {
		newPos.x -= size.height / 4;
	}
	else if (dirMove.x == DIR_RIGHT) {
		newPos.x += size.height / 4;
	}
	bool canMove = false;
	if (dirMove.x) {
		auto pos = newPos + dirMove * speed * Director::getInstance()->getAnimationInterval();
		canMove = Utility::CCUtility::checkTile(pos, "Meta", "collidable");
	}
	if (dirMove.y) {
		auto pos = newPos + dirMove * speed * Director::getInstance()->getAnimationInterval();
		auto pos1 = (newPos + Vec2(size.height / 4, 0)) + dirMove * speed * Director::getInstance()->getAnimationInterval();
		auto pos2 = (newPos + Vec2(-size.height / 4, 0)) + dirMove * speed * Director::getInstance()->getAnimationInterval();
		if (Utility::CCUtility::checkTile(pos, "Meta", "collidable") &&
			Utility::CCUtility::checkTile(pos1, "Meta", "collidable") &&
			Utility::CCUtility::checkTile(pos2, "Meta", "collidable")) {
			canMove = true;
		}
	}

	if (canMove) {
		this->getPhysicsBody()->setVelocity(dirMove * speed);
	}
	else {
		this->getPhysicsBody()->setVelocity(Vec2::ZERO);

	}

	int index = ORDER_BACKGROUND_LAYER;
	newPos = this->getPosition();
	if (!Utility::CCUtility::checkTile(Vec2(newPos.x, newPos.y), "Meta1", "isFront") ||
		!Utility::CCUtility::checkTile(Vec2(newPos.x - tileSize.width, newPos.y), "Meta1", "isFront") ||
		!Utility::CCUtility::checkTile(Vec2(newPos.x + tileSize.width, newPos.y), "Meta1", "isFront") ||
		!Utility::CCUtility::checkTile(Vec2(newPos.x, newPos.y + tileSize.width), "Meta1", "isFront") ||
		!Utility::CCUtility::checkTile(Vec2(newPos.x + tileSize.width, newPos.y + tileSize.width), "Meta1", "isFront") ||
		!Utility::CCUtility::checkTile(Vec2(newPos.x - tileSize.width, newPos.y + tileSize.width), "Meta1", "isFront")
		)
	{
		index = ORDER_MIDDLEGROUND_LAYER;
	}
	this->setLocalZOrder(index);

}

void EntityLife::update(float dt) {

	Entity::update(dt);
	if (dirMove.x || dirMove.y) {
		move();
	}
	else {
		auto body = this->getPhysicsBody();
		if (body != nullptr) {
			body->setVelocity(Vec2::ZERO);
		}
	}
}
