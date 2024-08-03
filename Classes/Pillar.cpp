#include "Pillar.h"


Pillar::Pillar() {
	hp = 5000;
	hpMax = 5000;
}

bool Pillar::initWithName(std::string name) {
	Sprite::create("");
	auto path = name + ".png";
	this->setTexture(path);
	this->name = name;
	initHpBar();
	initBody();
	this->scheduleUpdate();
	return true;
}

bool Pillar::initWithSprite(Sprite* sprite, std::string name) {
	if (!initWithTexture(sprite->getTexture(), sprite->getTextureRect()))
		return false;
	this->name = name;
	initHpBar();
	initBody();
	this->scheduleUpdate();
	return true;
}

void Pillar::initHpBar() {
	hpBar = Slider::create();
	hpBar->loadBarTexture(PATH_IMAGE_UI + "hp_pillar_bg.png");
	hpBar->loadProgressBarTexture(PATH_IMAGE_UI + "hp_pillar_progress.png");
	hpBar->setEnabled(false);
	auto percent = float(hp) / hpMax * 100;		
	hpBar->setPercent(percent);
	hpBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height + 15));
	this->addChild(hpBar, -1);
}

void Pillar::initBody() {
	auto body = PhysicsBody::createEdgeBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	body->setContactTestBitmask(PILLAR_CONTACT);
	body->setCategoryBitmask(PILLAR_CATEGORY);
	body->setCollisionBitmask(PILLAR_COLLISION);
	this->setPhysicsBody(body);
}

void Pillar::update(float dt) {
	auto percent = float(hp) / hpMax * 100;
	hpBar->setPercent(percent);
}