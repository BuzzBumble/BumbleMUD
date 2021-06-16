#include "GameServer.h"

#include "Socket.h"
#include "ClientCode.h"

#include <iostream>

bool GameServer::Init(const unsigned short& port) {
	if (!socket.Open() || !socket.Bind(port) || !socket.Listen(10)) {
		return false;
	}
	return true;
}

void GameServer::Accept() {
	net::Address clientAddr;
	int newfd = socket.Accept(clientAddr);

	std::cout << "[CONNECTION] FROM " << 
		clientAddr.GetIP1() << "." <<
		clientAddr.GetIP2() << "." <<
		clientAddr.GetIP3() << "." <<
		clientAddr.GetIP4() << ":" <<
		clientAddr.GetPort() <<
		std::endl;
}

