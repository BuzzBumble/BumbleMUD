#include "Character.h"

Character::Character(const std::string& name, int maxHealth)
	: name(name)
	, maxHealth(maxHealth)
	, currentHealth(maxHealth) {
}

bool Character::init() {
	AssignDobjID();
	return true;
}

std::string Character::getName() const {
	return name;
}

int Character::getMaxHealth() const {
	return maxHealth;
}

int Character::getCurrentHealth() const {
	return currentHealth;
}

std::pair<int, int> Character::getCoords() const {
	return coords;
}

int Character::takeDamage(int damage) {
	currentHealth -= damage;
	return currentHealth;
}

void Character::dealDamage(Character& victim, int damage) {
	victim.takeDamage(damage);
}
