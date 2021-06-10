#include "Room.h"

unsigned int Room::IDCounter = 1;

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

std::vector<Character*> Room::getCharacters() {
	return characters;
}

/*
std::vector<Enemy*> Room::getEnemies() {
	return enemies;
}

std::vector<Player*> Room::getPlayers() {
	return players;
}
*/

