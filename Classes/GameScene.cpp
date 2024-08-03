#include "GameScene.h"
#include "Utility.h"
#include "InputHandler.h"
#include "MyBodyParser.h"
#include <math.h>
#include "cocos/math/CCMath.h"
#include "MainMenuScene.h"
#include "GameManager.h"
#include "HubLayer.h"
#include "FileManager.h"
#include "SoundManager.h"

USING_NS_CC;


bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	turnCount = FileManager::getInstance()->getTurnCount();
	initPhysicsWorld();
	initMap();
	initPillar();
	initCharacter();
	initHubLayer();
	initListenerKeyBoard();
	initListenerPhysicsContact();
	initListenerMouse();
	initSchedule();
	SoundManager::getInstance()->playBackgroundMusic(PATH_SOUND + "Blizzard.mp3");
	return true;
}


void GameScene::update(float dt) {

	if (turn > turnCount) {
		auto fun = CallFunc::create([] {
			GameManager::getInstance()->gameOver(true);
			});
		this->runAction(Sequence::create(DelayTime::create(3), fun, NULL));
	}
	if (GameManager::getInstance()->getCharacter()->getHp() <= 0 ||
		GameManager::getInstance()->getPillar()->getHp() <= 0) {
		auto fun = CallFunc::create([] {
			GameManager::getInstance()->gameOver(false);
			});
		this->runAction(Sequence::create(DelayTime::create(3), fun, NULL));

	}
	GameManager::getInstance()->removeMonster();
}


void GameScene::updateMap(float dt) {

	auto camera = Director::getInstance()->getRunningScene()->getCameras().front();
	auto charPos = GameManager::getInstance()->getCharacter()->getPosition();
	Vec2 camPos = camera->getPosition();
	auto tileMap = GameManager::getInstance()->getTileMap();
	auto tileSize = tileMap->getTileSize();
	if (charPos.x > VISIBLE_SIZE_WIDTH / 2 && charPos.x < tileMap->getMapSize().width * tileSize.width - VISIBLE_SIZE_WIDTH / 2) {
		camPos.x = charPos.x;
	}
	if (charPos.y > VISIBLE_SIZE_HEIGHT / 2 && charPos.y < tileMap->getMapSize().height * tileSize.height - VISIBLE_SIZE_HEIGHT / 2) {
		camPos.y = charPos.y;
	}
	camera->setPosition(camPos);
	GameManager::getInstance()->getHubLayer()->setPosition(camPos - VISIBLE_SIZE / 2);
}

void GameScene::updateEventMouse(float dt) {
	if (InputHandler::getInstance()->isMouseDown(InputHandler::BUTTON_LEFT)) {
		auto camPos = Director::getInstance()->getRunningScene()->getCameras().front()->getPosition();
		auto location = InputHandler::getInstance()->getMouseLocation();
		location.y = VISIBLE_SIZE_HEIGHT - location.y;
		auto mousePos = camPos - VISIBLE_SIZE / 2 + location;
		auto character = GameManager::getInstance()->getCharacter();
		auto wpos = character->convertToWorldSpace(character->getWeapon()->getPosition());
		auto dir = mousePos - wpos;
		character->getWeapon()->setDirection(mousePos - character->getPosition());
		character->attack(dir);
	}
}

void GameScene::spawnMonster(float dt) {
	float time = 2;
	if (totalMonster[0] > 0) {
		auto fun = CallFunc::create([=] {
			addMonsterToScene(1);
			countMonster[0] = countMonster[0] + 1;
			});
		this->runAction(Repeat::create(Sequence::create(fun, DelayTime::create(time), nullptr), totalMonster[0]));
	}


	if (totalMonster[1] > 0) {
		auto fun = CallFunc::create([=] {
			addMonsterToScene(2);
			countMonster[1] ++;
			});
		this->runAction(Repeat::create(Sequence::create(fun, DelayTime::create(time), nullptr), totalMonster[1]));
	}

	if (totalMonster[2] > 0) {
		auto fun = CallFunc::create([=] {
			addMonsterToScene(3);
			countMonster[2] ++;
			});
		this->runAction(Repeat::create(Sequence::create(fun, DelayTime::create(time), nullptr), totalMonster[2]));
	}



	if (totalMonster[3] > 0) {
		auto fun = CallFunc::create([=] {
			addMonsterToScene(4);
			countMonster[3] ++;
			});
		this->runAction(Repeat::create(Sequence::create(fun, DelayTime::create(time), nullptr), totalMonster[3]));
	}

}

void GameScene::initMap() {
	auto tileMap = TMXTiledMap::create(PATH_MAP + "GameMap.tmx");
	for (int i = 1; ; i++)
	{
		auto bg = tileMap->getLayer("Background" + std::to_string(i));
		if (bg == nullptr)break;
		bg->setLocalZOrder(ORDER_BACKGROUND_LAYER);
	}

	for (int i = 1; ; i++)
	{
		auto mg = tileMap->getLayer("Middleground" + std::to_string(i));
		if (mg == nullptr)break;
		mg->setLocalZOrder(ORDER_MIDDLEGROUND_LAYER);
	}

	tileMap->getLayer("Meta")->setVisible(false);
	tileMap->getLayer("Meta1")->setVisible(false);

	GameManager::getInstance()->setTileMap(tileMap);
	this->addChild(tileMap);

}

void GameScene::initCharacter() {
	auto tileMap = GameManager::getInstance()->getTileMap();
	TMXObjectGroup* objects = tileMap->getObjectGroup("Objects");
	ValueMap playerPoint = objects->getObject("start");
	auto pPos = Vec2(playerPoint.at("x").asInt(), playerPoint.at("y").asInt());
	auto character = FileManager::getInstance()->getCharacterDefault("Mage");
	character->initWeapon("Gun");
	character->setPosition(pPos);
	GameManager::getInstance()->setCharacter(character);
	tileMap->addChild(character, ORDER_BACKGROUND_LAYER);
}

void GameScene::initMonsterData(float dt) {
	if (countMonster[0] >= totalMonster[0] && countMonster[1] >= totalMonster[1] && countMonster[2]
		>= totalMonster[2] && countMonster[3] >= totalMonster[3] && GameManager::getInstance()->isEmptyMonster()) {
		turn++;
		if (turn > turnCount) {
			return;
		}
		int count = FileManager::getInstance()->getMonsterCount(turn, 1);
		totalMonster[0] = count;
		count = FileManager::getInstance()->getMonsterCount(turn, 2);
		totalMonster[1] = count;
		count = FileManager::getInstance()->getMonsterCount(turn, 3);
		totalMonster[2] = count;
		count = FileManager::getInstance()->getMonsterCount(turn, 4);
		totalMonster[3] = count;

		countMonster[0] = 0;
		countMonster[1] = 0;
		countMonster[2] = 0;
		countMonster[3] = 0;
		this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::spawnMonster), 5);
	}
}

void GameScene::initHubLayer() {
	auto	hubLayer = HubLayer::create();
	GameManager::getInstance()->setHubLayer(hubLayer);
	this->addChild(hubLayer, ORDER_HUB_LAYER, "HubLayer");
}

void GameScene::initPillar() {
	auto pillar = Pillar::createWithSprite(Sprite::create(PATH_IMAGE_OBJECT + "Pillar.png"));
	auto tileMap = GameManager::getInstance()->getTileMap();
	TMXObjectGroup* objects = tileMap->getObjectGroup("Objects");
	ValueMap pillarPoint = objects->getObject("pillar");
	auto pPos = Vec2(pillarPoint.at("x").asInt(), pillarPoint.at("y").asInt());
	pillar->setPosition(pPos);
	GameManager::getInstance()->setPillar(pillar);
	tileMap->addChild(pillar, ORDER_MIDDLEGROUND_LAYER);

}

void GameScene::initPhysicsWorld() {
	auto world = this->getPhysicsWorld();
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_CONTACT);
	world->setGravity(Vec2::ZERO);
	GameManager::getInstance()->setPhysicsWorld(world);
}

void GameScene::initListenerMouse() {
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	listener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	listener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::initSchedule() {
	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateEventMouse));
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateMap));
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::initMonsterData));
}

void GameScene::onMouseDown(EventMouse* event) {
	InputHandler::getInstance()->onMouseDown(event);
}

void GameScene::onMouseMove(EventMouse* event) {
	InputHandler::getInstance()->onMouseMove(event);
}

void GameScene::onMouseUp(EventMouse* event) {
	InputHandler::getInstance()->onMouseUp(event);
}

void GameScene::initListenerKeyBoard() {
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
	InputHandler::getInstance()->onKeyDown((int)key);
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
	InputHandler::getInstance()->onKeyUp((int)key);
}

void GameScene::initListenerPhysicsContact() {
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameScene::onContactBegan(cocos2d::PhysicsContact& contact) {
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	if ((bodyA->getCollisionBitmask() == CHARACTER_COLLISION && bodyB->getCollisionBitmask() == BULLET_MONSTER_COLLISION) ||
		(bodyA->getCollisionBitmask() == BULLET_MONSTER_COLLISION && bodyB->getCollisionBitmask() == CHARACTER_COLLISION)) {
		if (bodyA->getCollisionBitmask() == CHARACTER_COLLISION) {
			auto cha = (Character*)bodyA->getNode();
			auto bullet = (Bullet*)bodyB->getNode();
			if (bullet != nullptr && cha != nullptr) {
				int hp = cha->getHp() - bullet->getDame();
				hp = hp < 0 ? 0 : hp;
				cha->setHp(hp);
				bullet->removeFromParentAndCleanup(true);
				if (hp <= 0) {
					cha->dead();
				}
			}
		}
		else {
			auto cha = (Character*)bodyB->getNode();
			auto bullet = (Bullet*)bodyA->getNode();
			if (bullet != nullptr && cha != nullptr) {

				int hp = cha->getHp() - bullet->getDame();
				hp = hp < 0 ? 0 : hp;
				cha->setHp(hp);
				bullet->removeFromParentAndCleanup(true);
				if (hp <= 0) {
					cha->dead();
				}
			}
		}
	}

	if ((bodyA->getCollisionBitmask() == BULLET_CHARACTER_COLLISION && bodyB->getCollisionBitmask() == MONSTER_COLLISION) ||
		(bodyA->getCollisionBitmask() == MONSTER_COLLISION && bodyB->getCollisionBitmask() == BULLET_CHARACTER_COLLISION)) {
		if (bodyA->getCollisionBitmask() == MONSTER_COLLISION) {
			auto monster = (Monster*)bodyA->getNode();
			auto bullet = (Bullet*)bodyB->getNode();
			if (bullet != nullptr && monster != nullptr) {
				int hp = monster->getHp() - bullet->getDame();
				hp = hp <= 0 ? 0 : hp;
				monster->setHp(hp);
				bullet->removeFromParentAndCleanup(true);
			}
		}
		else {
			auto monster = (Monster*)bodyB->getNode();
			auto bullet = (Bullet*)bodyA->getNode();
			if (bullet != nullptr && monster != nullptr) {

				int hp = monster->getHp() - bullet->getDame();
				hp = hp < 0 ? 0 : hp;
				monster->setHp(hp);
				bullet->removeFromParentAndCleanup(true);
			}
		}
	}

	if ((bodyA->getCollisionBitmask() == PILLAR_COLLISION && bodyB->getCollisionBitmask() == MONSTER_COLLISION) ||
		(bodyA->getCollisionBitmask() == MONSTER_COLLISION && bodyB->getCollisionBitmask() == PILLAR_COLLISION)) {
		if (bodyA->getCollisionBitmask() == PILLAR_COLLISION) {
			auto pil = (Pillar*)bodyA->getNode();
			auto monster = (Monster*)bodyB->getNode();
			if (monster != nullptr && pil != nullptr) {
				int hp = pil->getHp() - 200;
				hp = hp < 0 ? 0 : hp;
				pil->setHp(hp);
				monster->setHp(0);
			}
		}
		else {
			auto pil = (Pillar*)bodyB->getNode();
			auto monster = (Monster*)bodyA->getNode();
			if (monster != nullptr && pil != nullptr) {
				int hp = pil->getHp() - 200;
				hp = hp < 0 ? 0 : hp;
				pil->setHp(hp);
				monster->setHp(0);
			}
		}
	}
	return true;
}

void GameScene::addMonsterToScene(int gate) {
	auto tileMap = GameManager::getInstance()->getTileMap();
	TMXObjectGroup* objects = tileMap->getObjectGroup("Objects");


	std::string gates[] = { "west_gate", "north_gate", "east_gate","south_gate" };

	ValueMap point = objects->getObject(gates[gate - 1]);

	Vec2 pos(0, RandomHelper::random_int(2, 35));
	if (gate == 2 || gate == 4) {

		pos = Vec2(RandomHelper::random_int(2, 35), 0);
	}

	auto mPos = Vec2(point.at("x").asInt(), point.at("y").asInt()) + pos;
	auto m = FileManager::getInstance()->getMonster(turn, gate, countMonster[gate - 1]);
	m->setPosition(mPos);
	auto dirMove = (GameManager::getInstance()->getPillar()->getPosition() - mPos).getNormalized();
	m->setDirMove(dirMove);
	GameManager::getInstance()->addMonster(m);
	tileMap->addChild(m);

}