#pragma once

#include "cocos2d.h"
#include "Entity.h"

class Skill : public Entity
{
public:
	virtual bool init(std::string id);
	CC_SYNTHESIZE(bool, isMove, IsMove);
	CC_SYNTHESIZE(int, dame, Dame);
	CREATE_FUNC1(Skill, std::string);
};

