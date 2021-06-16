#pragma once
#include <string>


class Character {
public:
	Character() = default;
	Character(const std::string& name, int maxHealth);
	virtual bool init() = 0;

	unsigned long long getID() const;
	std::string getName() const;
	int getMaxHealth() const;
	int getCurrentHealth() const;
	std::pair<int, int> getCoords() const;

	int takeDamage(int damage);
	void dealDamage(Character& victim, int damage);

protected:
	unsigned long long id;
	std::pair<int, int> coords;
	std::string name;
	int maxHealth;
	int currentHealth;
};
