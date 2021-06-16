#include "Room.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Address.h"
#include "UDPSocket.h"
#include "Net.h"

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

	char buf[net::Socket::MAX_PACKET_SIZE];
	unsigned short port = 3030;
	net::UDPSocket sock;
	net::Address addr(127, 0, 0, 1, port);

	if (!sock.Open() || !sock.Bind(port)) {
		return -1;
	}

	std::vector<std::unique_ptr<Player>> serverPlayers;

	net::Address senderAddr;
	int numBytes = -1;
	std::cout << "Waiting for message..." << std::endl;
	numBytes = sock.Receive(senderAddr, buf, sizeof(buf));
	std::cout << "[RECEIVED] " << buf <<
		std::endl <<
		"FROM " <<
		senderAddr.GetIP1() << "." <<
		senderAddr.GetIP2() << "." <<
		senderAddr.GetIP3() << "." <<
		senderAddr.GetIP4() << ":" <<
		std::endl;
	char msgType = buf[0];
	const char* msgData = &buf[1];
	if (buf[0] == 1) {
		serverPlayers.emplace_back(std::make_unique<Player>(msgData, 100, senderAddr));
	}
	unsigned int connectedResponse = 1;
	sock.Send(senderAddr, (void*)&connectedResponse, sizeof(connectedResponse));

	char c;
	std::cin >> c;

	// Handle the connection
	// Move everything under this to Client
	return 0;
}
