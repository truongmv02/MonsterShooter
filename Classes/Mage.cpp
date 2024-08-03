#include <string>
#include "Mage.h"
#include "Utility.h"
#include "InputHandler.h"
#include "GameManager.h"

bool Mage::init() {
	this->initWithSpriteFrameName("Mage.png");
	initBody();
	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(Mage::updateEventKeyBoard));
	return true;
}

void Mage::initBody() {
	auto body = PhysicsBody::createEdgeBox(this->getContentSize(), PhysicsMaterial(1, 0, 1));
	body->setContactTestBitmask(CHARACTER_CONTACT);
	body->setCollisionBitmask(CHARACTER_COLLISION);
	body->setCategoryBitmask(CHARACTER_CATEGORY);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
}

void Mage::attack(Vec2 dir) {

	if (!weapon || isAttack || hp <= 0 || mp < weapon->getEnegryCost()) return;
	isAttack = true;
	weapon->attack(dir);
	//mp = mp - weapon->getEnegryCost();
	auto attackFinish = CallFunc::create([=] {isAttack = false; });
	auto action =
		Sequence::create(DelayTime::create(weapon->getGapTime()), attackFinish, nullptr);
	this->runAction(action);
}

void Mage::update(float dt) {
	Character::update(dt);
}
