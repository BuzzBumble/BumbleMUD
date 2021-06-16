#include "Enemy.h"

unsigned int Enemy::IDCounter = 1;

bool Enemy::init() {
	// Add character to the server
	id = IDCounter++;
	// If character was not added successfully
	return false;
	// Else
	return true;
}

