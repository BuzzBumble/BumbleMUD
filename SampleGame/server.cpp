#include "Room.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Address.h"
#include "Socket.h"
#include "Net.h"

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void displayMessage(const std::string& message, bool newline);
std::string receiveMessage();

int main() {
	if (!net::InitializeSockets()) {
		std::cout << "Could not initialize Winsock" << std::endl;
		return -1;
	}

	char buf[net::Socket::MAX_PACKET_SIZE];
	unsigned short port = 3030;
	net::Socket sock;
	net::Address addr(127, 0, 0, 1, port);

	if (!sock.Open(port)) {
		return -1;
	}

	std::vector<std::unique_ptr<Player>> serverPlayers;

	net::Address senderAddr;
	int numBytes = -1;
	numBytes = sock.Receive(senderAddr, buf, sizeof(buf));
	char msgType = buf[0];
	const char* msgData = &buf[1];
	if (buf[0] == 1) {
		serverPlayers.emplace_back(std::make_unique<Player>(msgData, 100, senderAddr));
	}
	unsigned int connectedResponse = 1;
	sock.Send(addr, (void*)&connectedResponse, sizeof(connectedResponse));

	std::string input;
	std::string introMessage = "Welcome to BumbleMUD\nWhat is your character's name? ";

	displayMessage(introMessage, true);

	input = receiveMessage();
	std::unique_ptr<Player>& player = serverPlayers.back();

	// Handle the connection


	// Move everything under this to Client
	displayMessage("Hello " + player->getName() + ". Let's get started", true);

	Room room(std::pair<int, int>(0, 0));
	room.addEnemy(std::make_unique<Enemy>("Gobulin", 50));
	room.addPlayer(player);
	room.init();

	displayMessage("You are in room " + std::to_string(room.getID()), true);

	std::cout << "Type 'room'" << std::endl;
	input = receiveMessage();

	if (input == "room") {
		std::cout << "Players: " << std::endl;
		for (const auto& roomPlayer : room.getPlayers()) {
			std::cout << roomPlayer->getName() << std::endl;
		}

		std::cout << "Enemies: " << std::endl;
		for (const auto& roomEnemy : room.getEnemies()) {
			std::cout << roomEnemy->getName() << std::endl;
		}
	}

	return 0;
}

void displayMessage(const std::string& message, bool newline) {
	std::cout <<
		std::endl <<
		"------------------------------------" <<
		std::endl <<
		"[SERVER]" <<
		std::endl <<
		message;
	if (newline) {
		std::cout << std::endl;
	}
}

std::string receiveMessage() {
	std::string str;
	std::cin >> str;
	return str;
}