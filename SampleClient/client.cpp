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
#include <thread>

#pragma warning(disable:4996) 

void displayMessage(const std::string& message, bool newline);
std::string receiveMessage();

void waitForMessage(net::TCPSocket sock) {
	int recvBytes;
	char buf[net::Socket::MAX_PACKET_SIZE];
	ServerMessage sm = ServerMessage();
	while (true) {
		recvBytes = sock.Receive(buf, net::Socket::MAX_PACKET_SIZE);
		sm.parse(buf);
		if (recvBytes < 1) {
			break;
		}
		std::cout << std::endl << sm << std::endl;
	}
}

int main() {
	std::string msg;
	std::thread recvThread;

	if (!net::InitializeSockets()) {
		std::cout << "Could not initialize Winsock" << std::endl;
		return -1;
	}

	GameManager gm;
	gm.init();
	gm.getMessage("welcome").display();


	unsigned short serverport = 3030;

	net::Address serverAddr(127, 0, 0, 1, serverport);

	net::TCPSocket sock;

	if (!sock.Open()) {
		std::cout << "Socket could not open" << std::endl;
		return -1;
	}

	if (!sock.Connect(serverAddr)) {
		std::cout << "Socket could not connect" << std::endl;
		return -1;
	}
	std::cout << "Connected to server" << std::endl;

	recvThread = std::thread(waitForMessage, sock);

	while (true) {
		std::cout <<  "Enter command: ";
		gm.readInput();
		msg = gm.getLastInput();
		if (msg == "exit") {
			closesocket(sock.GetHandle());
			break;
		}

		sock.Send(msg.c_str(), msg.size() + 1);
	}

	recvThread.join();

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
