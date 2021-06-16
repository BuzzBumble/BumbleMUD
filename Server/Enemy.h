#pragma once
#include "Character.h"
#include <string>

class Enemy : public Character {
public:
	Enemy() = default;
	Enemy(const std::string& name, int maxHealth) : Character(name, maxHealth) {}

	bool init();
private:
	static unsigned int IDCounter;
};
