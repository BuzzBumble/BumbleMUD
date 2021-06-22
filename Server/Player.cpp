#include "Player.h"

Player::Player(const std::string& name, const std::string& description, const net::Address& addr, int sockfd)
	: Character(name, description)
	, addr(addr)
	, sockfd(sockfd) {
}

bool Player::init() {
	// Add character to the server
	Character::init();
	// If character was not added successfully
	return false;
	// Else
	return true;
}
