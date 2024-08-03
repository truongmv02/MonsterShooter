#pragma once
#include <map>
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "IMonster.h"
#include "Character.h"

USING_NS_CC;
class FileManager
{
public:

	static FileManager* getInstance();
	Character* getCharacterDefault(std::string name);
	IMonster* getMonsterDefault(std::string name);
	IMonster* getMonster(int turn, int gate, int index);
	int getMonsterCount(int turn, int gate);
	int getTurnCount();
	std::map<int, Vector<IMonster*>> getMonsters(int turn);
private:
	FileManager();
	static FileManager* instance;
	rapidjson::Document character_default;
	rapidjson::Document monster_default;
	rapidjson::Document turn_default;
	rapidjson::size_t size;
};

