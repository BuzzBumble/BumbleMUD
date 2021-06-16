#include "Address.h"

#if PLATFORM == PLATFORM_WIN
#include <WinSock2.h>
#pragma comment(lib, "wsock32.lib")
#elif (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif

#include <iostream>

namespace net {
	Address::Address(unsigned char ip1,
		unsigned char ip2,
		unsigned char ip3,
		unsigned char ip4,
		unsigned short port)
		: port(port)
	{
		address = (
			(ip1 << 24) |
			(ip2 << 16) |
			(ip3 << 8) |
			ip4
		);

		sockAddr.sin_family = AF_INET;
		sockAddr.sin_addr.s_addr = htonl(address);
		sockAddr.sin_port = htons(port);
	}

	Address::Address(unsigned int addr, unsigned short port)
		: address(addr)
		, port(port) {

		sockAddr.sin_family = AF_INET;
		sockAddr.sin_addr.s_addr = htonl(address);
		sockAddr.sin_port = htons(port);
	}

	unsigned int Address::GetAddress() const {
		return address;
	}

	unsigned int Address::GetIP1() const {
		return address >> 24 & 0xFF;
	}

	unsigned int Address::GetIP2() const {
		return (address >> 16) & 0xFF;
	}

	unsigned int Address::GetIP3() const {
		return (address >> 8) & 0xFF;
	}

	unsigned int Address::GetIP4() const {
		return address & 0xFF;
	}

	unsigned short Address::GetPort() const {
		return port;
	}

	const sockaddr_in& Address::GetSockAddr() const {
		return sockAddr;
	}
}
