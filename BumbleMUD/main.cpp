#if PLATFORM == PLATFORM_WIN
#include <WinSock2.h>
#pragma comment(lib, "wsock32.lib")
#elif (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif
#include <iostream>
#include "Socket.h"
#include "Address.h"

#define PACKET_SIZE 256

bool InitializeSockets() {
#if PLATFORM == PLATFORM_WIN
	WSADATA WSAData;
	return WSAStartup(MAKEWORD(2, 2), &WSAData) == NO_ERROR;
#else
	return true;
#endif
}

void ShutdownSockets() {
#if PLATFORM == PLATFORM_WIN
	WSACleanup();
#endif
}

int main() {
	if (!InitializeSockets()) {
		std::cout << "Could not initialize Winsock" << std::endl;
		return -1;
	}
	unsigned short port = 3030;

	Socket sock;
	Address addr(127, 0, 0, 1, port);
	unsigned char msg[] = "I'm gay";
	unsigned char buf[256];

	if (!sock.Open(port)) {
		// Socket failed to open
		return -1;
	}

	std::cout << "Socket opened" << std::endl;

	sock.Send(addr, msg, sizeof(msg));

	int bytes;
	while (true) {
		Address sender;
		bytes = sock.Receive(sender, buf, sizeof(buf));
		if (bytes > 0) {
			std::cout << "[DATA] " << buf << std::endl;
		}
	}

	return 0;
}

