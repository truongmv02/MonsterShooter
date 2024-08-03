#include "CharacterFactory.h"
#include <string>
#include <string.h>
Character* CharacterFactory::getCharacter(std::string name) {
	if (name == "Mage") {
		return	Mage::create();
	}
	return nullptr;
}