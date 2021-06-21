#pragma once
#include "Character.h"
#include "Address.h"

class Player : public Character {
public:
	Player() = default;
	Player(const std::string& name, int maxHealth, const net::Address& addr, int sockfd)
		: Character(name, maxHealth)
		, addr(addr)
		, sockfd(sockfd){}

	bool init();
private:
	net::Address addr;
	int sockfd;
};
