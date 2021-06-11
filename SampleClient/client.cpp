#include "Address.h"
#include "Socket.h"
#include "Net.h"
#include "Character.h"

#include <string>
#include <iostream>
#pragma warning(disable:4996) 

void displayMessage(const std::string& message, bool newline);
std::string receiveMessage();

int main() {
	if (!net::InitializeSockets()) {
		std::cout << "Could not initialize Winsock" << std::endl;
		return -1;
	}

	char buf[net::Socket::MAX_PACKET_SIZE];

	unsigned short serverport = 3030;

	net::Address serverAddr(127, 0, 0, 1, serverport);

	net::Socket sock;

	if (!sock.Open()) {
		return -1;
	}

	int numBytes = -1;

	char msg[256];
	char c;
	std::string name = "Steven";
	msg[0] = 1;
	name.copy(&msg[1], name.size());
	msg[name.size() + 1] = '\0';
	
	std::cin >> c;
	sock.Send(serverAddr, msg, strlen(msg)+1);
	std::cout << "[SENT] " << msg << std::endl;
	sock.Receive(serverAddr, buf, sizeof(buf));

	std::cout << "[RECEIVED] " << buf << std::endl;

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
/*
	std::string input;
	std::string introMessage = "Welcome to BumbleMUD\nWhat is your character's name? ";

	displayMessage(introMessage, true);

	input = receiveMessage();
	std::unique_ptr<Player>& player = serverPlayers.back();



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
*/
