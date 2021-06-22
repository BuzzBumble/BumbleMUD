#include "Character.h"

Character::Character(const std::string& name, const std::string& description)
	: DataObject(name, description) {}

bool Character::init() {
	AssignDobjID();
	return true;
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
