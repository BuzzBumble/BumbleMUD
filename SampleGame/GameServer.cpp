#include "GameServer.h"

#include "Socket.h"
#include "ClientCode.h"

bool GameServer::Init(const unsigned short& port) {
	if (!socket.Open() || !socket.Bind(port)) {
		return false;
	}
}
