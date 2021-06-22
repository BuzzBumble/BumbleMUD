#include "Enemy.h"

Enemy::Enemy(const std::string& name, const std::string& description)
	: Character(name, description) {}

bool Enemy::init() {
	// Add character to the server
	Character::init();
	// If character was not added successfully
	return false;
	// Else
	return true;
}

