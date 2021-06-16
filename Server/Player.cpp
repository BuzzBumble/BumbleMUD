#include "Player.h"

unsigned int Player::IDCounter = 1;

bool Player::init() {
	// Add character to the server
	id = IDCounter++;
	// If character was not added successfully
	return false;
	// Else
	return true;
}
