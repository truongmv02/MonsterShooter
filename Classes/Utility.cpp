#include "Utility.h"
#include "GameManager.h"

using namespace Utility;

Vec2 UI::getScreenCenter() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto screenCenter = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	return screenCenter;
}


void UI::addCenterBackgroundToScene(string filePath, Scene* scene) {
	auto background = Sprite::create(filePath);
	background->setPosition(Utility::UI::getScreenCenter());
	scene->addChild(background);
}

void UI::addCenterBackgroundToLayer(string filePath, Layer* layer) {
	auto background = Sprite::create(filePath);
	background->setPosition(Utility::UI::getScreenCenter());
	layer->addChild(background);
}

Animation* CCUtility::createAnimation(string frameName, int frameCount, float delay, int loop) {

	Vector<SpriteFrame*> frameAni;
	for (int i = 1; i < frameCount; i++) {
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		string str = frameName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		if (frame != NULL)
			frameAni.pushBack(frame);
	}
	Animation* ani = Animation::createWithSpriteFrames(frameAni, delay, loop);
	return ani;
}

Animation* CCUtility::createAnimation(string frameName, float delay, int loop) {

	Vector<SpriteFrame*> frameAni;
	for (int i = 1; ; i++) {
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		string str = frameName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		if (frame == NULL) break;
		frameAni.pushBack(frame);
	}
	Animation* ani = Animation::createWithSpriteFrames(frameAni, delay, loop);
	return ani;
}

Animate* CCUtility::getAnimate(string animateName, int frameCount, float delay, int loop) {
	auto animation = createAnimation(animateName, frameCount, delay, loop);
	return  Animate::create(animation);
}

Animate* CCUtility::getAnimate(string animateName, float delay, int loop) {
	auto animation = createAnimation(animateName, delay, loop);
	return  Animate::create(animation);
}

Animate* CCUtility::getAnimate(string animateName) {
	auto animation = AnimationCache::getInstance()->getAnimation(animateName);
	return Animate::create(animation);
}

Action* CCUtility::getAction(Animate* animate1, Animate* animate2, bool repeatForever) {
	auto action = Sequence::create(animate1, animate2, nullptr);
	if (repeatForever) {
		return RepeatForever::create(action);
	}
	return action;
}

Action* CCUtility::createActionReverse(Animate* animate, bool repeatForever) {
	auto animateReverse = animate->reverse();
	return getAction(animate, animateReverse, repeatForever);
}

float CCUtility::changingAngleAccordingToCoordinateSystem(float calculatedAngle) {

	if ((calculatedAngle >= 0 && calculatedAngle <= 90) || (calculatedAngle >= 90 && calculatedAngle <= 180)) {
		calculatedAngle = calculatedAngle;
	}
	else if (calculatedAngle < 0 && calculatedAngle >= -90) {
		calculatedAngle = 270 + (90 + calculatedAngle);
	}
	else if (calculatedAngle < -90 && calculatedAngle >= -180) {
		calculatedAngle = 180 + (180 + calculatedAngle);
	}

	return calculatedAngle;
}

void CCUtility::setDir(Vec2 dirMove, Vec2& dir) {
	if (dirMove.x) {
		dir.x = dirMove.x;
	}
	else {
		dir.y = dirMove.y;
	}
}

bool CCUtility::checkTile(Vec2 position, std::string layer, std::string property)
{
	Vec2 tileCoord = positionToIndex(position);
	auto tileSize = GameManager::getInstance()->getTileMap()->getMapSize();
	if (tileCoord.x >= tileSize.width || tileCoord.y >= tileSize.height || tileCoord.x < 0 || tileCoord.y < 0) return false;
	int tileGid = GameManager::getInstance()->getTileMap()->getLayer(layer)->getTileGIDAt(tileCoord);
	if (tileGid != 0) {

		auto val = GameManager::getInstance()->getTileMap()->getPropertiesForGID(tileGid);
		if (!val.isNull()) {
			auto valueMap = val.asValueMap();
			if (valueMap.size() > 0) {
				std::string collision = valueMap.at(property).asString();
				if (collision.compare("true") == 0) {
					return false;
				}
			}
		}
	}
	return true;
}

Vec2 CCUtility::positionToIndex(Vec2 position)
{
	auto tileMap = GameManager::getInstance()->getTileMap();
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return Vec2(x, y);
}