#include "Address.h"
#include "Socket.h"
#include "Net.h"
#include "Character.h"

#include <string>
#include <iostream>

int main() {
	if (!net::InitializeSockets()) {
		std::cout << "Could not initialize Winsock" << std::endl;
		return -1;
	}

	unsigned char buf[net::Socket::MAX_PACKET_SIZE];
	unsigned short port = 3031;
	net::Socket sock;
	net::Address addr(127, 0, 0, 1, port);

	if (!sock.Open(port)) {
		return -1;
	}

	char msg[256];
	std::string name = "Steven";
	msg[0] = 1;
	name.copy(&msg[1], name.size());
	msg[name.size() + 1] = '\0';

	std::cout << msg << std::endl;

	// Now send the msg to the server

	return 0;
}