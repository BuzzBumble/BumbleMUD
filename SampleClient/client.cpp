#include "Address.h"
#include "TCPSocket.h"
#include "Net.h"
#include "Character.h"
#include "GameManager.h"
#include "ServerMessage.h"
#include "json.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#pragma warning(disable:4996) 

void displayMessage(const std::string& message, bool newline);
std::string receiveMessage();

int main() {
	if (!net::InitializeSockets()) {
		std::cout << "Could not initialize Winsock" << std::endl;
		return -1;
	}

	GameManager gm;
	gm.init();
	gm.getMessage("welcome").display();

	char buf[net::Socket::MAX_PACKET_SIZE];

	unsigned short serverport = 3030;

	net::Address serverAddr(127, 0, 0, 1, serverport);

	net::TCPSocket sock;

	if (!sock.Open()) {
		std::cout << "Socket could not open" << std::endl;
		return -1;
	}

	while (!sock.Connect(serverAddr)) {}
	std::cout << "Connected to server" << std::endl;
	sock.Receive(buf, net::Socket::MAX_PACKET_SIZE);
	ServerMessage sMsg = ServerMessage(buf);
	sMsg.init();
	std::cout << "[RECEIVED] " << buf << std::endl;

	std::cout << "Enter command: ";
	gm.readInput();
	std::string msg = gm.getLastInput();

	sock.Send(msg.c_str(), msg.size() + 1);

	std::cin.get();
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
