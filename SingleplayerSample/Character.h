#pragma once
#include <string>


class Character {
public:
	Character() = default;
	Character(std::string name, int maxHealth);
	bool init();

	int getID();
	std::string getName();
	int getMaxHealth();
	int getCurrentHealth();
	std::pair<int, int> getCoords();

	int takeDamage(int damage);
	void dealDamage(Character& victim, int damage);

private:
	static unsigned int IDCounter;
	unsigned int id = 0;
	std::pair<int, int> coords;
	std::string name;
	int maxHealth;
	int currentHealth;
};
