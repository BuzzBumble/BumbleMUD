#pragma once

#include "Socket.h"
#include "Player.h"
#include <memory>
#include <vector>

class GameServer {
public:
	GameServer() = default;
	bool Init(const unsigned short& port);

	int Listen();

private:
	net::Socket socket;
	std::vector<std::unique_ptr<Player>> activePlayers;
};
