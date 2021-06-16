#include "Room.h"

unsigned int Room::IDCounter = 1;

bool Room::init() {
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

std::vector<const Player*> Room::getPlayers() {
	return players;
}

std::vector<std::unique_ptr<Enemy>>& Room::getEnemies() {
	return enemies;
}

void Room::addEnemy(std::unique_ptr<Enemy> enemy) {
	enemies.push_back(std::move(enemy));
}

void Room::addPlayer(const std::unique_ptr<Player>& player) {
	players.push_back(player.get());
}

/*
std::vector<Enemy*> Room::getEnemies() {
	return enemies;
}

std::vector<Player*> Room::getPlayers() {
	return players;
}
*/

