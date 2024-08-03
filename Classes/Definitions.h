#pragma once

#define VISIBLE_SIZE         Director::getInstance()->getVisibleSize()
#define VISIBLE_SIZE_WIDTH   Director::getInstance()->getVisibleSize().width
#define VISIBLE_SIZE_HEIGHT  Director::getInstance()->getVisibleSize().height


#define PATH_IMAGE_CHARACTER    std::string("Image/Character/")
#define PATH_IMAGE_WEAPON       std::string("Image/Weapon/")
#define PATH_IMAGE_MONSTER      std::string("Image/Monster/")
#define PATH_IMAGE_UI           std::string("Image/UI/")
#define PATH_IMAGE_OBJECT       std::string("Image/Object/")
#define PATH_IMAGE_ITEM         std::string("Image/Item/")
#define PATH_IMAGE_BULLET       std::string("Image/Bullet/")
#define PATH_IMAGE_EFFECT       std::string("Image/Effect/")
#define PATH_IMAGE_NUMBER       std::string("Image/Number/")
#define PATH_MAP                std::string("Map/")
#define PATH_SOUND              std::string("Sound/")

#define PATH_DATA_PLIST         std::string("Data/Plist/")
#define PATH_DATA_DEFAULT       std::string("Data/Default/")

#define NUMBER_STRING "0123456789+-"


#define TRANSITION_TIME 0.5

#define ORDER_BACKGROUND_LAYER      1
#define ORDER_PLAYER                10
#define ORDER_MIDDLEGROUND_LAYER    20
#define ORDER_HUB_LAYER             100


#define TAG_ACTION_MOVE     1
#define TAG_ACTION_IDLE     2
#define TAG_ACTION_ATTACK   3


#define CHARACTER_COLLISION          0b000000001
#define MONSTER_COLLISION            0b000010010
#define BULLET_CHARACTER_COLLISION   0b000000100
#define BULLET_MONSTER_COLLISION     0b000001000
#define PILLAR_COLLISION             0b000100000

#define CHARACTER_CATEGORY           0b000001000
#define MONSTER_CATEGORY             0b000100100
#define BULLET_CHARACTER_CATEGORY    0b000000010
#define BULLET_MONSTER_CATEGORY      0b000000001
#define PILLAR_CATEGORY              0b000010000

#define CHARACTER_CONTACT            0b000000001
#define MONSTER_CONTACT              0b000010010
#define BULLET_CHARACTER_CONTACT     0b000000100
#define BULLET_MONSTER_CONTACT       0b000001000
#define PILLAR_CONTACT               0b000100000


enum Direction {
	DIR_RIGHT = 1,
	DIR_LEFT = -1,
	DIR_UP = 1,
	DIR_DOWN = -1
};



#define CREATE_WITH_NAME_FUNC(__TYPE__) \
static __TYPE__* createWithName(std::string name) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithName(name)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CREATE_WITH_SPRITE_FUNC(__TYPE__) \
static __TYPE__* createWithSprite(Sprite *sprite,std::string name = "") \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithSprite(sprite, name)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}