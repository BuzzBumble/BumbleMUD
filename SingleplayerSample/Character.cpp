#include "Character.h"

unsigned int Character::IDCounter = 0;

Character::Character(std::string name, int maxHealth)
	: name(name)
	, maxHealth(maxHealth)
	, currentHealth(maxHealth) {
}

bool Character::Init() {
	// Add character to the server
	id = IDCounter++;
	// If character was not added successfully
	return false;
	// Else
	return true;
}

int Character::getID() {
	return id;
}

std::string Character::getName() {
	return name;
}

int Character::getMaxHealth() {
	return maxHealth;
}

int Character::getCurrentHealth() {
	return currentHealth;
}

std::pair<int, int> Character::getCoords() {
	return coords;
}

int Character::takeDamage(int damage) {
	currentHealth -= damage;
	return currentHealth;
}

void Character::dealDamage(Character& victim, int damage) {
	victim.takeDamage(damage);
}
