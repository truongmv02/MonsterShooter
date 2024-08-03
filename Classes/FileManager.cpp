#include "FileManager.h"
#include "Definitions.h"
#include "CharacterFactory.h"
#include "MonsterFactory.h"

FileManager* FileManager::instance = nullptr;

FileManager::FileManager() {

	std::string buf = FileUtils::getInstance()->getStringFromFile(PATH_DATA_DEFAULT + "Character.json");
	character_default.Parse(buf.c_str());

	buf = FileUtils::getInstance()->getStringFromFile(PATH_DATA_DEFAULT + "Monster.json");
	monster_default.Parse(buf.c_str());
	buf = FileUtils::getInstance()->getStringFromFile(PATH_DATA_DEFAULT + "Turn.json");
	turn_default.Parse(buf.c_str());

}

FileManager* FileManager::getInstance() {
	if (instance == nullptr) {
		instance = new FileManager();
	}
	return instance;
}

Character* FileManager::getCharacterDefault(std::string name) {
	auto c = CharacterFactory::getCharacter(name);
	rapidjson::Value& list = character_default["Characters"];
	for (rapidjson::SizeType i = 0; i < list.Size(); i++)
	{
		if (list[i]["Name"].GetString() == name) {
			c->setSpeed(list[i]["Speed"].GetInt());
			c->setHp(list[i]["Hp"].GetInt());
			c->setHp(list[i]["HpMax"].GetInt());
			c->setMp(list[i]["Mp"].GetInt());
			c->setMpMax(list[i]["MpMax"].GetInt());
			return c;
		}
	}
	return c;
}

IMonster* FileManager::getMonsterDefault(std::string name) {
	auto m = MonsterFactory::getMonster(name);

	rapidjson::Value& list = monster_default["Monsters"];
	for (rapidjson::SizeType i = 0; i < list.Size(); i++)
	{
		if (list[i]["Name"].GetString() == name) {
			m->setSpeed(list[i]["Speed"].GetInt());
			m->setAttackSpeed(list[i]["AttackSpeed"].GetFloat());
			m->setHp(list[i]["Hp"].GetInt());
			m->setHpMax(list[i]["HpMax"].GetInt());
			m->setDame(list[i]["Dame"].GetFloat());
			return m;
		}
	}
	return m;
}

int FileManager::getTurnCount() {
	rapidjson::Value& turns = turn_default["Turns"];
	return turns.Size();
}

int FileManager::getMonsterCount(int turn, int gate) {
	turn--;
	rapidjson::Value& turns = turn_default["Turns"];
	rapidjson::Value& gates = turns[turn]["Gates"];
	if (gates.Size() <= 0) { return 0; }

	int count = 0;
	for (rapidjson::SizeType i = 0; i < gates.Size(); i++)
	{
		if (gates[i]["Gate"] == gate) {
			rapidjson::Value& list = gates[i]["Monsters"];
			for (int index = 0; index < list.Size(); index++)
			{
				count += list[index]["Count"].GetInt();
			}
			break;
		}
	}

	return count;
}

IMonster* FileManager::getMonster(int turn, int gate, int index) {

	turn--;
	rapidjson::Value& turns = turn_default["Turns"];
	rapidjson::Value& gates = turns[turn]["Gates"];
	float p = turns[turn]["Percent"].GetFloat();
	for (rapidjson::SizeType i = 0; i < gates.Size(); i++)
	{
		if (gates[i]["Gate"] == gate) {
			rapidjson::Value& list = gates[i]["Monsters"];
			int count = list[0]["Count"].GetInt();
			int _index = 0;
			int count1 = count;
			for (int j = 1; j < list.Size(); j++)
			{
				count += list[j]["Count"].GetInt();
				if (index < count && index >= count1) {
					_index = j;
					break;
				}
				count1 = count;
			}

			std::string name = list[_index]["Name"].GetString();
			auto m = getMonsterDefault(name);
			m->setHp(m->getHp() + m->getHp() * p);
			m->setHpMax(m->getHpMax() + m->getHpMax() * p);
			m->setDame(m->getDame() + m->getDame() * p);
			return m;
		}
	}
}

std::map< int, Vector<IMonster*>> FileManager::getMonsters(int turn) {
	turn--;
	std::map <int, Vector<IMonster*>> monsterMap;

	rapidjson::Value& turns = turn_default["Turns"];
	rapidjson::Value& gates = turns[turn]["Gates"];


	float p = turns[turn]["Percent"].GetFloat();
	// Get Gates Data
	for (rapidjson::SizeType i = 0; i < gates.Size(); i++)
	{
		int gate = gates[i]["Gate"].GetInt();
		rapidjson::Value& list = gates[i]["Monsters"];
		Vector<IMonster*> monsterList;
		// Get monsters
		for (rapidjson::SizeType i = 0; i < list.Size(); i++)
		{
			int count = list[i]["Count"].GetInt();
			std::string name = list[i]["Name"].GetString();
			for (rapidjson::SizeType i = 0; i < count; i++)
			{
				auto m = getMonsterDefault(name);
				m->setHp(m->getHp() + m->getHp() * p);
				m->setHpMax(m->getHpMax() + m->getHpMax() * p);
				m->setDame(m->getDame() + m->getDame() * p);
				monsterList.pushBack(m);

			}
		}
		monsterMap[gate] = monsterList;
	}
	return monsterMap;

}

