#pragma once
#include "Character.h"
#include <string>

class Enemy : public Character {
public:
	Enemy() = default;
	Enemy(const std::string& name, int maxHealth) : Character(name, maxHealth) {}

	bool init(const unsigned long long& newID);
private:
};
