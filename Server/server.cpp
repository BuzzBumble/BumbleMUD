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

//void UDPTestServer();
//void TCPTestServer();

int main() {
	if (!net::InitializeSockets()) {
		std::cout << "Could not initialize Winsock" << std::endl;
		return -1;
	}
	unsigned short port = 3030;

	GameServer server;
	server.Init(port);
	server.Accept();

	char c;
	std::cin >> c;

	// Handle the connection
	// Move everything under this to Client
	return 0;
}
/*
void TCPTestServer() {
	char buf[net::Socket::MAX_PACKET_SIZE];
	unsigned short port = 3030;
	net::TCPSocket sock;
	net::Address addr(127, 0, 0, 1, port);

	if (!sock.Open() || !sock.Bind(port) || !sock.Listen(5)) {
		return;
	}

	std::vector<std::unique_ptr<Player>> serverPlayers;

	net::Address senderAddr;
	std::cout << "Waiting for connection..." << std::endl;
	int newfd = sock.Accept(senderAddr);
	std::cout << "[CONNECTION] FROM " << 
		senderAddr.GetIP1() << "." <<
		senderAddr.GetIP2() << "." <<
		senderAddr.GetIP3() << "." <<
		senderAddr.GetIP4() << ":" <<
		std::endl;

	int numBytes = -1;
	std::cout << "Waiting for message..." << std::endl;
	numBytes = sock.Receive(newfd, buf, sizeof(buf));
	std::cout << "[RECEIVED] " << numBytes << " BYTES:" <<
		std::endl <<
		buf <<
		std::endl;
	char msgType = buf[0];
	const char* msgData = &buf[1];
	if (buf[0] == 1) {
		serverPlayers.emplace_back(std::make_unique<Player>(msgData, 100, senderAddr));
	}
	unsigned int connectedResponse = 1;
	sock.Send((void*)&connectedResponse, sizeof(connectedResponse));
}
*/
/*
void UDPTestServer() {
	char buf[net::Socket::MAX_PACKET_SIZE];
	unsigned short port = 3030;
	net::UDPSocket sock;
	net::Address addr(127, 0, 0, 1, port);

	if (!sock.Open() || !sock.Bind(port)) {
		return;
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
}
*/
