#pragma once

#include "TCPSocket.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <string>

class GameServer {
public:
	static const unsigned short BUFSIZE;
	static const unsigned short MAXPLAYERS;
	GameServer() = default;
	bool Init(const unsigned short& port);

	void Run();

	unsigned int Accept();
	int Receive(unsigned int recfd);
	int Send(unsigned int sendfd, const std::string& data);
	bool ConnectPlayer(const std::string& name, const std::string& description, const net::Address& clientAddr, int sockfd);
private:
	net::TCPSocket socket;
	std::vector<std::unique_ptr<Player>> activePlayers;
	char buf[1024];
	unsigned int listenfd = 0;
	fd_set rset = {};
	unsigned int maxfdp1 = 0;
};
