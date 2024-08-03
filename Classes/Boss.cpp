#include "Boss.h"

Boss::Boss() {

}

bool Boss::initWithName(std::string name) {
	if (!EntityLife::initWithName(name)) {
		return false;
	}
	initHpBar();
	return true;
}

bool Boss::initWithSprite(Sprite* sprite, std::string name) {
	if (!EntityLife::initWithSprite(sprite, name)) {
		return false;
	}
	initHpBar();
	return true;
}


void Boss::update(float dt) {


}

void Boss::attack(float dt) {

}

void Boss::initHpBar() {
	hpBar = Slider::create();
	hpBar->loadBarTexture(PATH_IMAGE_UI + "hp_boss_bg.png");
	hpBar->loadProgressBarTexture(PATH_IMAGE_UI + "hp_boss_progress.png");
	hpBar->setEnabled(false);
	auto size = this->getContentSize();
	hpBar->setPosition(Vec2(size.width / 2, size.height + 10));
	hpBar->setPercent(100);
	this->addChild(hpBar);
}