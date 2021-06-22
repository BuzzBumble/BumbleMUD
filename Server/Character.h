#pragma once
#include <string>
#include "DataObject.h"

class Character : public DataObject {
public:
	Character() = default;
	Character(const std::string& name, const std::string& description);
	virtual bool init();

	int getMaxHealth() const;
	int getCurrentHealth() const;
	std::pair<int, int> getCoords() const;

	int takeDamage(int damage);
	void dealDamage(Character& victim, int damage);

protected:
	std::pair<int, int> coords;
	int maxHealth = 0;
	int currentHealth = 0;
};
