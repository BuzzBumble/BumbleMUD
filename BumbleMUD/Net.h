#pragma once
#if PLATFORM == PLATFORM_WIN
#include <WinSock2.h>
#pragma comment(lib, "wsock32.lib")
#elif (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif

namespace net {
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
};
