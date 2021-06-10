#pragma once
#include <vector>

class Enemy;
class Player;

class Room {
public:
	Room() = default;
	
	Room(const std::pair<int, int>& coords)
		: coords(coords) {}

	// "Places" room into world
	bool Init();

	unsigned int getID();
	std::vector<Enemy*> getEnemies();
	std::vector<Player*> getPlayers();

private:
	static int IDCounter;
	unsigned int id;
	std::pair<int, int> coords;
	std::vector<Enemy*> enemies;
	std::vector<Player*> players;
};
