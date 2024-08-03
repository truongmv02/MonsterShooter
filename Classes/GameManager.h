

#pragma once
#include <map>
#include <queue>
#include "cocos2d.h"
#include "Character.h"
#include "Pillar.h"
#include "HubLayer.h"
#include "IMonster.h"

USING_NS_CC;
class GameManager
{
public:
	static GameManager* getInstance();
	void gameOver(bool isWin);
	void pauseGame();
	void resumeGame();
	void pauseGame(Vector<Node*> nodes);
	void resumeGame(Vector<Node*> nodes);
	inline TMXObjectGroup* getObjectGroup(std::string groupName) { return tileMap->getObjectGroup(groupName); }
	void removeMonster();
	bool isEmptyMonster();
	inline void addMonster(IMonster* monster) { this->monsterList.pushBack(monster); }
public:
	CC_SYNTHESIZE(TMXTiledMap*, tileMap, TileMap);
	CC_SYNTHESIZE(HubLayer*, hubLayer, HubLayer);
	CC_SYNTHESIZE(Character*, character, Character);
	CC_SYNTHESIZE(Pillar*, pillar, Pillar);
	CC_SYNTHESIZE(PhysicsWorld*, world, PhysicsWorld);
private:
	GameManager() {}
	static GameManager* instance;
	Vector<IMonster*> monsterList;
};