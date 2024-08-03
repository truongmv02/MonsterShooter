#include "MonsterFactory.h"
IMonster* MonsterFactory::getMonster(std::string name) {
	if (name == "Bat" || name == "Gosth" || name == "Ariman" || name == "Deathspirit") {
		return	Monster::createWithSprite(Sprite::createWithSpriteFrameName(name + ".png"), name);
	}
	return nullptr;
}