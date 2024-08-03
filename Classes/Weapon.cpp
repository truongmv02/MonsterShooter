#include "Weapon.h"
#include "Utility.h"
#include "chipmunk/chipmunk.h"
#include <string>
#include "Bullet.h"
#include "GameManager.h"
#include "SoundManager.h"

Weapon::Weapon() :Entity() {
	bulletName = "bullet";
	gapTime = 0.2;
	enegryCost = 2;
	dame = 50;
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
}

bool Weapon::initWithName(std::string name) {
	if (!Entity::initWithName(name)) {
		return false;
	}
	this->scheduleUpdate();
	return true;
}


bool Weapon::initWithSprite(Sprite* sprite, std::string name) {
	if (!Entity::initWithSprite(sprite, name)) {
		return false;
	}

	this->scheduleUpdate();
	return true;
}

void Weapon::createBullet(Vec2 dir) {
	auto bullet = Bullet::createWithSprite(Sprite::create(PATH_IMAGE_BULLET + bulletName + ".png"));
	bullet->getPhysicsBody()->setContactTestBitmask(BULLET_CHARACTER_CONTACT);
	bullet->getPhysicsBody()->setCategoryBitmask(BULLET_CHARACTER_CATEGORY);
	bullet->getPhysicsBody()->setCollisionBitmask(BULLET_CHARACTER_COLLISION);
	bullet->setDame(this->dame);
	dir.normalize();
	auto weaponSize = this->getContentSize();
	auto wPos = getParent()->convertToWorldSpace(getPosition());
	auto pt = (weaponSize.width / 2) * dir.getNormalized() + wPos;

	bullet->setPointStart(wPos);
	bullet->setPosition(pt);
	bullet->getPhysicsBody()->setVelocity(dir * bullet->getFlyingSpeed());
	bullet->setRotation(-CC_RADIANS_TO_DEGREES(dir.getAngle()));
	GameManager::getInstance()->getTileMap()->addChild(bullet, 1);
	SoundManager::getInstance()->playEffect(PATH_SOUND + "laser.mp3");
}

void Weapon::attack(Vec2 dir) {
	createBullet(dir);
}

void Weapon::update(float dt) {
	auto angle = CC_RADIANS_TO_DEGREES(dir.getAngle());
	if (dynamic_cast<Character*>(getParent())) {
		auto character = dynamic_cast<Character*> (getParent());
		auto size = character->getContentSize();
		if (angle > 80 && angle < 100 || angle > -100 && angle < -80)
			setPosition(size.width / 2, size.height / 4);
		if (dir.x < 0)
			setPosition(size.width / 2 - 10, size.height / 4);
		else
			setPosition(size.width / 2 + 10, size.height / 4);
	}
	setFlippedY(dir.x <= 0.0f);
	setRotation(-angle);
}
