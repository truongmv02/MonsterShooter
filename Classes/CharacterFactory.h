

#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "Mage.h"
USING_NS_CC;

class CharacterFactory
{
public:
	static Character* getCharacter(std::string name);
};
