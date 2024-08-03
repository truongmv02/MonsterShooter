#pragma once

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "Character.h"
#include "Pillar.h"
#include "Monster.h"
#include "StateBoard.h"

USING_NS_CC;
using namespace ui;
class GameScene : public Scene
{
public:

	virtual bool init();

	void initMap();
	void initCharacter();
	void initHubLayer();
	void initMonsterData(float dt = 0);
	void addMonsterToScene(int gate);
	void initPillar();
	void initPhysicsWorld();
	void initListenerKeyBoard();
	void initListenerPhysicsContact();
	void initListenerMouse();
	void initSchedule();
	void onMouseUp(EventMouse* event);
	void onMouseMove(EventMouse* event);
	void onMouseDown(EventMouse* event);
	void onKeyPressed(EventKeyboard::KeyCode key, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode key, Event* event);
	bool onContactBegan(PhysicsContact& contact);
	void update(float dt);
	void updateMap(float dt);
	void updateEventMouse(float dt);
	void spawnMonster(float dt);
	CREATE_FUNC(GameScene);
private:
	int turn = 0;
	int turnCount;
	int countMonster[4] = { 0 };
	int totalMonster[4] = { 0 };
};

