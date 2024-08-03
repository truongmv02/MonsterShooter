#include "Monster.h"
#include "Utility.h"
#include "GameManager.h"
Monster::Monster() {
	attackRange = VISIBLE_SIZE.width / 2;
	speed = 30;
	dame = 50;
	hp = 200;
	hpMax = 200;
}

bool Monster::initWithName(std::string name) {
	if (!EntityLife::initWithName(name)) {
		return false;
	}
	initHpBar();
	return true;
}

bool Monster::initWithSprite(Sprite* sprite, std::string name) {
	if (!EntityLife::initWithSprite(sprite, name)) {
		return false;
	}
	initHpBar();
	initBody();
	auto action = Utility::CCUtility::getAnimate(name, 0.1, -1);
	this->runAction(action);
	this->scheduleUpdate();
	return true;
}

void Monster::initBody() {
	auto body = PhysicsBody::createEdgeBox(this->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
	body->setContactTestBitmask(MONSTER_CONTACT);
	body->setCollisionBitmask(MONSTER_COLLISION);
	body->setCategoryBitmask(MONSTER_CATEGORY);
	this->setPhysicsBody(body);
}

void Monster::update(float dt) {
	//if (this->getParent() == nullptr)return;
	if (hp <= 0) {
		remove();
		return;
	}
	dir = dirMove;
	attack();
	EntityLife::update(dt);
	int percent = (float)hp / hpMax * 100;
	hpBar->setPercent(percent);
}

void Monster::attack() {
	if (hp <= 0 || isAttack) return;
	auto character = GameManager::getInstance()->getCharacter();
	auto dirAttack = character->getPosition() - this->getPosition();
	if (dirAttack.getLength() <= attackRange && character->getHp() > 0) {
		isAttack = true;
		Vec2 angle20 = Vec2::forAngle(CC_DEGREES_TO_RADIANS(20));
		createBullet(dirAttack);
		int rd = RandomHelper::random_int(1, 100);
		if (rd <= 15) {
			createBullet(dirAttack.rotate(angle20));
			angle20.y = -angle20.y;
			createBullet(dirAttack.rotate(angle20));
		}
		auto action = CallFunc::create([=] {
			this->isAttack = false;
			});
		this->runAction(Sequence::create(DelayTime::create(attackSpeed), action, nullptr));
	}
}

void Monster::createBullet(Vec2 dirAttack) {
	dirAttack.normalize();
	auto bullet = Bullet::createWithSprite(Sprite::create(PATH_IMAGE_BULLET + "Bullet4.png"));
	bullet->getPhysicsBody()->setContactTestBitmask(BULLET_MONSTER_CONTACT);
	bullet->getPhysicsBody()->setCategoryBitmask(BULLET_MONSTER_CATEGORY);
	bullet->getPhysicsBody()->setCollisionBitmask(BULLET_MONSTER_COLLISION);
	bullet->setPointStart(this->getPosition());
	bullet->setDame(this->dame);
	bullet->setRotation(-CC_RADIANS_TO_DEGREES(dirAttack.getAngle()));
	bullet->getPhysicsBody()->setVelocity(dirAttack * 150);
	bullet->setPosition(this->getPosition());
	this->getParent()->addChild(bullet, 1);

}

void Monster::initHpBar() {
	hpBar = Slider::create();
	hpBar->loadBarTexture(PATH_IMAGE_UI + "hp_bg.png");
	hpBar->loadProgressBarTexture(PATH_IMAGE_UI + "hp_progress.png");
	hpBar->setEnabled(false);
	auto size = this->getContentSize();
	hpBar->setPosition(Vec2(size.width / 2, size.height + 15));
	hpBar->setPercent(100);
	this->addChild(hpBar);
}

void Monster::remove() {
	auto explosion = Sprite::createWithSpriteFrameName("Explosion1.png");
	explosion->setPosition(this->getPosition());
	auto action = Utility::CCUtility::getAnimate("Explosion1", 0.05);
	auto finishAction = CallFunc::create([=] {
		explosion->removeFromParentAndCleanup(true);
		});
	this->getParent()->addChild(explosion);
	explosion->runAction(Sequence::create(action, finishAction, nullptr));
	this->removeFromParentAndCleanup(true);
}