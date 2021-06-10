#pragma once

#include "Enemy.h"
#include <vector>
#include <string>
#include <memory>

class Player;

class Room {
public:
	Room() = default;
	
	Room(const std::pair<int, int>& coords)
		: coords(coords) {};

	// "Places" room into world
	bool init();

	unsigned int getID();

	// std::vector<Enemy*> getEnemies();
	// std::vector<Player*> getPlayers();

	void addEnemy(std::unique_ptr<Enemy> enemy);
	void addPlayer(const std::unique_ptr<Player>& player);

	std::vector<const Player*> getPlayers();
	std::vector<std::unique_ptr<Enemy>>& getEnemies();

private:
	static unsigned int IDCounter;
	unsigned int id = 0;
	std::pair<int, int> coords;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<const Player*> players;
};
