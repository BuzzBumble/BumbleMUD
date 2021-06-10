#include "Room.h"
#include "Enemy.h"
#include "Player.h"

int Room::IDCounter = 0;

bool Room::Init() {
	// Step 1: Add room

	// If no issues adding this room
		id = IDCounter++;
		return true;
	// Else return an error
		return false;
}

unsigned int Room::getID() {
	return id;
}
