#pragma once
#include "Character.h"
#include "Address.h"

class Player : public Character {
public:
	Player() = default;
	Player(const std::string& name, int maxHealth, const net::Address& addr)
		: Character(name, maxHealth)
		, addr(addr){}

	bool init();
private:
	static unsigned int IDCounter;
	net::Address addr;
};
