#include "Enemy.h"

Enemy::Enemy(const std::string& name)
	: Character(name) {}

bool Enemy::init() {
	// Add character to the server
	Character::init();
	// If character was not added successfully
	return false;
	// Else
	return true;
}

