#pragma once

#include "net_common.h"

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
