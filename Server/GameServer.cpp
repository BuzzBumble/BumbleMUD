#include "GameServer.h"
#include "Responder.h"

#include <iostream>

const unsigned short GameServer::BUFSIZE = 1024;
const unsigned short GameServer::MAXPLAYERS = 64;

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
	return recv(recfd, buf, BUFSIZE, 0);
}

int GameServer::Send(unsigned int sendfd, const std::string& dataStr) {
	return send(sendfd, dataStr.c_str(), dataStr.size() + 1, 0);
}

unsigned int GameServer::Accept() {
	net::Address clientAddr;
	int newfd = socket.Accept(clientAddr);
	if (newfd == -1) {
		std::cerr << "[ERROR] GameServer::Accept()" << std::endl;
		return 0;
	}
	FD_SET(newfd, &rset);
	maxfdp1 = max(maxfdp1, static_cast<unsigned int>(newfd + 1));

	std::cout << "[CONNECTION] FROM " << 
		clientAddr.GetIP1() << "." <<
		clientAddr.GetIP2() << "." <<
		clientAddr.GetIP3() << "." <<
		clientAddr.GetIP4() << ":" <<
		clientAddr.GetPort() <<
		std::endl;

	ConnectPlayer("TestPlayer", "Test Description", clientAddr, newfd);

	return newfd;
}

bool GameServer::ConnectPlayer(const std::string& name, const std::string& description, const net::Address& clientAddr, int sockfd) {
	if (activePlayers.size() >= MAXPLAYERS) {
		// Player Limit reached
		return false;
	}

	activePlayers.emplace_back(std::make_unique<Player>(name, description, clientAddr, sockfd));
	Responder res(Responder::Directive::ConnectPlayer, *activePlayers.back().get());
	Send(sockfd, res.GetResponse());

	return true;
}
