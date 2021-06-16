#pragma once

#include "TCPSocket.h"
#include "Player.h"
#include <memory>
#include <vector>

class GameServer {
public:
	GameServer() = default;
	bool Init(const unsigned short& port);

	void Accept();

private:
	net::TCPSocket socket;
	std::vector<std::unique_ptr<Player>> activePlayers;
};
