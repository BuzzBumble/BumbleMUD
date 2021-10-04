#include "Room.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Address.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "Net.h"
#include "GameServer.h"

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main() {
	if (!net::InitializeSockets()) {
		std::cout << "Could not initialize Winsock" << std::endl;
		return -1;
	}
	unsigned short port = 3030;

	GameServer server;

	server.Init(port);
	server.Run();

	// Handle the connection
	// Move everything under this to Client
	return 0;
}
