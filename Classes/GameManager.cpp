#include "GameManager.h"
#include "GameScene.h"
GameManager* GameManager::instance = nullptr;


GameManager* GameManager::getInstance() {
	if (instance == nullptr) {
		instance = new GameManager();
	}
	return instance;
}

bool GameManager::isEmptyMonster() {
	return monsterList.size() == 0;
}

void GameManager::removeMonster() {
	for (int i = 0; i < monsterList.size(); i++)
	{
		if (monsterList.at(i)->getHp() <= 0) {
			monsterList.erase(i);
		}
	}
}

void GameManager::gameOver(bool isWin) {
	hubLayer->getPauseBtn()->setVisible(false);
	if (isWin) {
		hubLayer->getVictoryLayer()->setVisible(true);
	}
	else {

		hubLayer->getGameOverLayer()->setVisible(true);
	}
	world->setSpeed(0);
	auto runningScene = Director::getInstance()->getRunningScene();
	runningScene->unscheduleAllCallbacks();
	auto x = runningScene->getChildren();
	pauseGame(x);
}

void GameManager::pauseGame() {
	hubLayer->getPauseBtn()->setEnabled(false);
	hubLayer->getPauseLayer()->setVisible(true);
	world->setSpeed(0);
	auto runningScene = Director::getInstance()->getRunningScene();
	runningScene->unscheduleAllCallbacks();
	auto x = runningScene->getChildren();
	pauseGame(x);
}

void GameManager::pauseGame(Vector<Node*> nodes) {

	if (nodes.size() == 0) {
		return;
	}
	for (auto x : nodes)
	{
		auto name = x->getName();
		if (x->getName() == "PauseLayer" || x->getName() == "GameOverLayer") {
			continue;
		}
		x->pause();
		pauseGame(x->getChildren());
	}
}

void GameManager::resumeGame() {
	hubLayer->getPauseBtn()->setEnabled(true);
	world->setSpeed(1.0f);
	auto runningScene = Director::getInstance()->getRunningScene();
	if (dynamic_cast<GameScene*>(runningScene)) {
		dynamic_cast<GameScene*>(runningScene)->initSchedule();
	}
	auto x = runningScene->getChildren();
	resumeGame(x);
}

void GameManager::resumeGame(Vector<Node*> nodes) {
	if (nodes.size() == 0) {
		return;
	}
	for (auto x : nodes)
	{
		if (x->getName() == "PauseLayer" || x->getName() == "GameOverLayer") {
			continue;
		}
		x->resume();
		resumeGame(x->getChildren());
	}
}