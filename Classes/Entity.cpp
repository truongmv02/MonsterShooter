#include "Entity.h"


Entity::Entity() {
	dir = Vec2(DIR_LEFT, 0);
}

bool Entity::initWithName(std::string name) {
	Sprite::create("");
	auto path = name + ".png";
	this->setTexture(path);
	this->name = name;
	return true;
}

bool Entity::initWithSprite(Sprite* sprite, std::string name) {
	if (!initWithTexture(sprite->getTexture(), sprite->getTextureRect()))
		return false;
	this->name = name;
	return true;
}


void Entity::update(float dt) {
	this->setFlippedX(dir.x <= 0);
}