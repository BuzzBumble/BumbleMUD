#pragma once
#include "Character.h"
#include <string>

class Enemy : public Character {
public:
	Enemy() = default;
	Enemy(const std::string& name);

	bool init();
private:
};
