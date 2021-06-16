#include "GameServer.h"

#include <iostream>

const unsigned short GameServer::BUFSIZE = 1024;

bool GameServer::Init(const unsigned short& port) {
	if (!socket.Open() || !socket.Bind(port) || !socket.Listen(10)) {
		return false;
	}

	FD_ZERO(&rset);
	listenfd = socket.GetHandle();
	FD_SET(listenfd, &rset);
	maxfdp1 = listenfd + 1;

	return true;
}

void GameServer::Run() {
	int nrdy = 0;
	fd_set tmp_rset;
	while (true) {
		tmp_rset = rset;
		nrdy = select(maxfdp1, &tmp_rset, NULL, NULL, NULL);
		if (nrdy >= 0) {
			for (unsigned int i = 1; i < maxfdp1; i++) {
				if (FD_ISSET(i, &rset)) {
					if (i == listenfd) {
						Accept();
					}
					else {
						Receive(i);
					}
				}
			}
		}
		else {
			#if (PLATFORM == PLATFORM_WINDOWS)
			std::cout << "ERROR CODE: " << WSAGetLastError() << std::endl;
			#elif (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX)
			std::cout << "ERROR CODE: " << errno << std::endl;
			#endif
		}
	}
}

int GameServer::Receive(unsigned int recfd) {
	int n = recv(recfd, buf, BUFSIZE, 0);
	std::cout << buf << std::endl;
	return n;
}

unsigned int GameServer::Accept() {
	net::Address clientAddr;
	unsigned int newfd = socket.Accept(clientAddr);
	FD_SET(newfd, &rset);
	maxfdp1 = max(maxfdp1, newfd + 1);

	std::cout << "[CONNECTION] FROM " << 
		clientAddr.GetIP1() << "." <<
		clientAddr.GetIP2() << "." <<
		clientAddr.GetIP3() << "." <<
		clientAddr.GetIP4() << ":" <<
		clientAddr.GetPort() <<
		std::endl;

	return newfd;
}

