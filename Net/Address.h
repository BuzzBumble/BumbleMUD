#pragma once
#include "net_common.h"

namespace net {
	class Address {
	public:
		Address() = default;

		Address(unsigned char ip1,
			unsigned char ip2,
			unsigned char ip3,
			unsigned char ip4,
			unsigned short port);

		Address(unsigned int addr, unsigned short port);

		unsigned int GetAddress() const;

		unsigned int GetIP1() const;
		unsigned int GetIP2() const;
		unsigned int GetIP3() const;
		unsigned int GetIP4() const;

		unsigned short GetPort() const;

		const sockaddr_in& GetSockAddr() const;

	private:
		sockaddr_in sockAddr;
		unsigned int address;
		unsigned short port;
	};
}
