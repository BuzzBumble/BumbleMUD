#pragma once
#include "Character.h"
#include <string>

class Enemy : public Character {
public:
	Enemy() = default;
	Enemy(const std::string& name, const std::string& description);

	bool init();
private:
};
