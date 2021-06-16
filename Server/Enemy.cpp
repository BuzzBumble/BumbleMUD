#include "Enemy.h"

bool Enemy::init(const unsigned long long& newID) {
	// Add character to the server
	id = newID;
	// If character was not added successfully
	return false;
	// Else
	return true;
}

