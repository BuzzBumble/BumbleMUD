#pragma once
#include <string>
#include "DataObject.h"

class Character : public DataObject {
public:
	Character() = default;
	Character(const std::string& name, int maxHealth);
	virtual bool init();

	std::string getName() const;
	int getMaxHealth() const;
	int getCurrentHealth() const;
	std::pair<int, int> getCoords() const;

	int takeDamage(int damage);
	void dealDamage(Character& victim, int damage);

protected:
	std::pair<int, int> coords;
	std::string name;
	int maxHealth;
	int currentHealth;
};
