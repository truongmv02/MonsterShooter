

#pragma once
#include "cocos2d.h"
#include "IMonster.h"
#include "Monster.h"
USING_NS_CC;

class MonsterFactory
{
public:
	static IMonster* getMonster(std::string name);
};
