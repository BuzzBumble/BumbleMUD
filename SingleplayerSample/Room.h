#pragma once

#include <vector>

class Character;

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
	std::vector<Character*> getCharacters();

	std::string getInfo();

private:
	static unsigned int IDCounter;
	unsigned int id = 0;
	std::pair<int, int> coords;
	// std::vector<Enemy*> enemies;
	// std::vector<Player*> players;
	std::vector<Character*> characters;
};
