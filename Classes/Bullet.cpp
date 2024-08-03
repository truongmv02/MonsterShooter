#include "Bullet.h"
#include "Utility.h"
#include "GameManager.h"

Bullet::Bullet() {
	this->flyingSpeed = 1000;
	this->distanceFly = VISIBLE_SIZE_WIDTH * 1.5;
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
}

bool Bullet::initWithName(std::string name) {
	if (!Entity::initWithName(name)) {
		return false;
	}
	initBody();
	this->scheduleUpdate();
	return true;
}

bool Bullet::initWithSprite(Sprite* sprite, std::string name) {
	if (!Entity::initWithSprite(sprite, name)) {
		return false;
	}
	initBody();
	this->scheduleUpdate();
	return true;
}

void Bullet::initBody() {
	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2, PHYSICSSHAPE_MATERIAL_DEFAULT);
	body->setContactTestBitmask(1);
	body->setCollisionBitmask(1);
	this->setPhysicsBody(body);
}

void Bullet::update(float dt) {
	auto length = (this->getPosition() - pointStart).getLength();
	if (length >= distanceFly) {
		this->removeFromParentAndCleanup(true);
		return;
	}
	auto pillarBox = GameManager::getInstance()->getPillar()->getBoundingBox();
	if (pillarBox.containsPoint(this->getPosition())) {
		return;
	}
	if (!Utility::CCUtility::checkTile(this->getPosition(), "Meta", "collidable")) {

		auto explosion = Sprite::createWithSpriteFrameName("Explosion1.png");
		auto action = Utility::CCUtility::getAnimate("Explosion1", 0.05);
		auto actionFinish = CallFunc::create([=] {
			explosion->removeFromParentAndCleanup(true);
			});
		this->getParent()->addChild(explosion);
		explosion->setPosition(this->getPosition());
		explosion->runAction(Sequence::create(action, actionFinish, nullptr));

		this->removeFromParentAndCleanup(true);
	}

}