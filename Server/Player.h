#pragma once
#include "Character.h"
#include "Address.h"

class Player : public Character {
public:
	Player() = default;
	Player(const std::string& name, const net::Address& addr, int sockfd);

	bool init();
private:
	net::Address addr;
	int sockfd;
};
